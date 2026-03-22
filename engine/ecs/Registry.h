// Lightweight, cache-friendly ECS registry
#pragma once

#include "Entity.h"

#include <cstdint>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>
#include <utility>

namespace kylie::ecs {

class Registry {
public:
    Entity create() {
        if (!freeList_.empty()) {
            auto id = freeList_.back();
            freeList_.pop_back();
            return Entity{id, versions_[id]};
        }
        Entity e{static_cast<Entity::id_type>(versions_.size()), 0};
        versions_.push_back(0);
        return e;
    }

    bool valid(Entity e) const {
        return e.id < versions_.size() && versions_[e.id] == e.version;
    }

    void destroy(Entity e) {
        if (!valid(e)) return;
        for (auto& [_, pool] : pools_) {
            pool->remove(e.id, versions_[e.id]);
        }
        ++versions_[e.id];
        freeList_.push_back(e.id);
    }

    template <typename T, typename... Args>
    T& emplace(Entity e, Args&&... args) {
        auto& pool = poolFor<T>();
        return pool.emplace(e, std::forward<Args>(args)...);
    }

    template <typename T>
    bool has(Entity e) const {
        auto it = pools_.find(std::type_index(typeid(T)));
        if (it == pools_.end()) return false;
        return static_cast<Pool<T>*>(it->second.get())->contains(e);
    }

    template <typename T>
    T& get(Entity e) {
        return poolFor<T>().get(e);
    }

    template <typename T>
    void remove(Entity e) {
        auto it = pools_.find(std::type_index(typeid(T)));
        if (it != pools_.end()) {
            static_cast<Pool<T>*>(it->second.get())->remove(e.id, versions_[e.id]);
        }
    }

    template <typename T, typename Func>
    void forEach(Func&& fn) {
        auto& pool = poolFor<T>();
        for (std::size_t i = 0; i < pool.entities.size(); ++i) {
            Entity e{pool.entities[i], versions_[pool.entities[i]]};
            fn(e, pool.data[i]);
        }
    }

private:
    struct PoolBase {
        virtual ~PoolBase() = default;
        virtual void remove(Entity::id_type id, Entity::version_type version) = 0;
    };

    template <typename T>
    struct Pool : PoolBase {
        std::vector<T> data;
        std::vector<Entity::id_type> entities;
        std::vector<std::size_t> sparse;  // index into dense arrays

        template <typename... Args>
        T& emplace(Entity e, Args&&... args) {
            ensureSparse(e.id);
            auto idx = data.size();
            sparse[e.id] = idx;
            entities.push_back(e.id);
            data.emplace_back(std::forward<Args>(args)...);
            return data.back();
        }

        bool contains(Entity e) const {
            return e.id < sparse.size() && sparse[e.id] != npos && entities[sparse[e.id]] == e.id;
        }

        T& get(Entity e) {
            return data[sparse[e.id]];
        }

        void remove(Entity::id_type id, Entity::version_type) override {
            if (id >= sparse.size()) return;
            auto idx = sparse[id];
            if (idx == npos) return;
            auto last = data.size() - 1;
            data[idx] = std::move(data[last]);
            entities[idx] = entities[last];
            sparse[entities[idx]] = idx;
            data.pop_back();
            entities.pop_back();
            sparse[id] = npos;
        }

    private:
        static constexpr std::size_t npos = static_cast<std::size_t>(-1);

        void ensureSparse(std::size_t id) {
            if (id >= sparse.size()) {
                sparse.resize(id + 1, npos);
            }
        }
    };

    template <typename T>
    Pool<T>& poolFor() const {
        auto key = std::type_index(typeid(T));
        auto it = pools_.find(key);
        if (it == pools_.end()) {
            auto pool = std::make_unique<Pool<T>>();
            auto* ptr = pool.get();
            const_cast<Registry*>(this)->pools_.emplace(key, std::move(pool));
            return *ptr;
        }
        return *static_cast<Pool<T>*>(it->second.get());
    }

    std::vector<Entity::version_type> versions_;
    std::vector<Entity::id_type> freeList_;
    std::unordered_map<std::type_index, std::unique_ptr<PoolBase>> pools_;
};

}  // namespace kylie::ecs
