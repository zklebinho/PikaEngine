#include "PythonBridge.h"

#include <iostream>

#ifdef PIKA_ENABLE_PYTHON
#include <Python.h>
#endif

namespace pika::scripting {

bool PythonBridge::initialize() {
#ifdef PIKA_ENABLE_PYTHON
    if (!Py_IsInitialized()) {
        Py_Initialize();
    }
    return Py_IsInitialized();
#else
    std::cerr << "[PythonBridge] PIKA_ENABLE_PYTHON is OFF; initialization skipped\n";
    return false;
#endif
}

void PythonBridge::shutdown() {
#ifdef PIKA_ENABLE_PYTHON
    if (Py_IsInitialized()) {
        Py_Finalize();
    }
#endif
}

bool PythonBridge::callEntityUpdate(const std::string& module,
                                    const std::string& function,
                                    ecs::Entity entity,
                                    ecs::Registry& registry,
                                    float deltaSeconds) {
#ifdef PIKA_ENABLE_PYTHON
    if (!Py_IsInitialized()) {
        std::cerr << "[PythonBridge] Python not initialized\n";
        return false;
    }
    PyObject* pName = PyUnicode_FromString(module.c_str());
    if (!pName) return false;
    PyObject* pModule = PyImport_Import(pName);
    Py_DECREF(pName);
    if (!pModule) {
        PyErr_Print();
        std::cerr << "[PythonBridge] Failed to import module " << module << "\n";
        return false;
    }
    PyObject* pFunc = PyObject_GetAttrString(pModule, function.c_str());
    if (!pFunc || !PyCallable_Check(pFunc)) {
        std::cerr << "[PythonBridge] Function not callable: " << function << "\n";
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
        return false;
    }

    // For now we pass only dt and entity id; registry pointer could be exposed via capsule later.
    PyObject* args = Py_BuildValue("(kf)", static_cast<unsigned long>(entity.id), deltaSeconds);
    PyObject* result = PyObject_CallObject(pFunc, args);
    Py_XDECREF(result);
    Py_DECREF(args);
    Py_DECREF(pFunc);
    Py_DECREF(pModule);
    if (PyErr_Occurred()) {
        PyErr_Print();
        return false;
    }
    return true;
#else
    (void)module;
    (void)function;
    (void)entity;
    (void)registry;
    (void)deltaSeconds;
    std::cerr << "[PythonBridge] PIKA_ENABLE_PYTHON is OFF; call skipped\n";
    return false;
#endif
}

}  // namespace pika::scripting
