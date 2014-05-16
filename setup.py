from distutils.core import setup, Extension


setup(
    ext_modules=[Extension("hafiz_num_reader", ["NumReaderExt.cpp"])],
)

