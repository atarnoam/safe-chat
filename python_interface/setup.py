from setuptools import setup, Extension

aesmodule = Extension(
    'aes',
    sources=['aesmodule.c',
             '../src/key_schedule.c',
             '../src/gf_operations.c'],
    include_dirs=['../include']
)

setup(
    name='aes',
    version='1.2',
    ext_modules=[aesmodule]
)
