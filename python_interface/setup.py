from distutils.core import setup
from distutils.extension import Extension
setup(name='aes', version='1.0', ext_modules=[Extension('aes', ['aesmodule.c'])])
