#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Mar 15 19:38:22 2018

@author: raven
"""

from distutils.core import setup, Extension
from Cython.Build import cythonize

ext = Extension("dsp_module", sources = ["dsp_module.pyx", "./recdigitalfiltersprogs/sines.c"], libraries=["m"])

setup(
      name = "dsp_module",
      ext_modules = cythonize([ext])
      )