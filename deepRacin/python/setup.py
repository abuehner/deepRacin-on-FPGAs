from distutils.core import setup
import os

setup(name='deepracin',
      version='',
      description='Python interface of deepRacin: deep resource-aware OpenCL inference networks',
      author='Jan Eric Lenssen',
      author_email='janeric.lenssen@tu-dortmund.de',
      package_dir={ '': os.path.normcase('/home/buehner/deepracin/python') },
      packages=['deepracin'])


