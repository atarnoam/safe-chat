//
// Created by Rami on 16/02/2018.
//

#include <Python.h>
#include "key_schedule.h"


static PyObject *hello_aes(PyObject *self, PyObject *args) {
    printf("hello\n");
    Py_RETURN_NONE;
}

static PyObject *key_expansion_aes(PyObject *self, PyObject *args) {
    Py_RETURN_NONE;
}

static PyMethodDef AESMethods[] = {
        {"hello", hello_aes, METH_VARARGS,
                "saying hello."},
        {"nothing", key_expansion_aes, METH_VARARGS,
                "do nothing."},
        {NULL, NULL, 0, NULL}        /* Sentinel */
};


PyMODINIT_FUNC initaes(void) {
    (void) Py_InitModule("aes", AESMethods);
}
