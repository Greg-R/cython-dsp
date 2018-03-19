#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Mar 15 19:34:42 2018

@author: raven
"""


cdef extern from "./recdigitalfiltersprogs/sines.h":
    int sinegen( int argc, char *argv[] )


def sine_gen(argc, argv):
    cdef char * args[4]
    args[:] = argv
    sinegen(argc, args)

    