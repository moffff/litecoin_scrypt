#include <Python.h>

#include "Lyra2.h"

static PyObject *scrypt_getpowhash(PyObject *self, PyObject *args)
{
    char *output;
    PyObject *value;
#if PY_MAJOR_VERSION >= 3
    PyBytesObject *input;
#else
    PyStringObject *input;
#endif
    if (!PyArg_ParseTuple(args, "S", &input))
        return NULL;
    Py_INCREF(input);
    output = PyMem_Malloc(32);

#if PY_MAJOR_VERSION >= 3
    LYRA2(BEGIN(output), 32, BEGIN((char *)PyBytes_AsString((PyObject*) input)), 80, BEGIN(PyObject*->nVersion), 80, 2, PyObject*->nHeight + 1, 256);
#else
    /*LYRA2(BEGIN(output), 32, BEGIN((char *)PyBytes_AsString((PyObject*) input)), 80, BEGIN(PyObject*->nVersion), 80, 2, PyObject*->nHeight + 1, 256);*/
#endif
    Py_DECREF(input);
#if PY_MAJOR_VERSION >= 3
    value = Py_BuildValue("y#", output, 32);
#else
    value = Py_BuildValue("s#", output, 32);
#endif
    PyMem_Free(output);
    return value;
}

static PyMethodDef ScryptMethods[] = {
    { "getPoWHash", scrypt_getpowhash, METH_VARARGS, "Returns the proof of work hash using scrypt" },
    { NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef ScryptModule = {
    PyModuleDef_HEAD_INIT,
    "ltc_scrypt",
    "...",
    -1,
    ScryptMethods
};

PyMODINIT_FUNC PyInit_ltc_scrypt(void) {
    return PyModule_Create(&ScryptModule);
}

#else

PyMODINIT_FUNC initltc_scrypt(void) {
    (void) Py_InitModule("ltc_scrypt", ScryptMethods);
}
#endif
