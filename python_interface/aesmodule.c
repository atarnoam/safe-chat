//
// Created by Rami on 16/02/2018.
//

#include <Python.h>

static PyObject *hello_aes(PyObject *self, PyObject *args) {
    printf("hello\n");
    Py_RETURN_NONE;
}

static PyMethodDef AESMethods[] = {
        {"hello", hello_aes, METH_VARARGS,
                "saying hello."},
        {NULL, NULL, 0, NULL}        /* Sentinel */
};


PyMODINIT_FUNC initaes(void) {
    (void) Py_InitModule("aes", AESMethods);
}
