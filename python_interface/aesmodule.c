//
// Created by Rami on 16/02/2018.
//

#include <python2.7/Python.h>
#include "key_schedule.h"


static PyObject *hello_aes(PyObject *self, PyObject *args) {
    printf("hello\n");
    Py_RETURN_NONE;
}

static PyObject *key_expansion_aes(PyObject *self, PyObject *args) {
    PyObject *key_obj;
    Py_buffer *key;

    if (!PyArg_ParseTuple(args, "0", &key_obj))
        return NULL;
    if (!PyObject_CheckBuffer(key_obj))
        return NULL;
    if (!PyObject_GetBuffer(key_obj, key, PyBUF_SIMPLE))
        return NULL;

    // allocate the expanded key
    word* expanded_key_bytes = PyMem_Malloc(60*sizeof(byte));
    if (!expanded_key_bytes)
        return NULL;

    key_schedule(key->buf, expanded_key_bytes);
    Py_buffer *expanded_key_buffer = PyMem_Malloc(sizeof(Py_buffer));


}

static PyMethodDef AESMethods[] = {
        {"hello", hello_aes, METH_VARARGS,
                "saying hello."},
        {"key_expand", key_expansion_aes, METH_VARARGS,
                "expand aes key. return memview of expanded result."},
        {NULL, NULL, 0, NULL}
};


PyMODINIT_FUNC initaes(void) {
    (void) Py_InitModule("aes", AESMethods);
}
