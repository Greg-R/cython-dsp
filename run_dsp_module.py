#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Mar 15 19:36:07 2018

@author: raven
"""

import dsp_module

args = ["sines", "./recdigitalfiltersprogs/sines3.def", "2000", "1024"]
argsEncoded = [x.encode('UTF-8') for x in args]

from wurlitzer import sys_pipes
with sys_pipes():
    dsp_module.sine_gen(4, argsEncoded)
    
from wurlitzer import pipes

with pipes() as (out, err):
    dsp_module.sine_gen(4, argsEncoded)

#  stdout is a giant string.
stdout = out.read()

#  Transform stdout into something that matplotlib can digest.

import matplotlib.pyplot as plt

import numpy as np

#plt.plot(stdout)

waveformAlpha = stdout.split('\n')

waveformNumeric = []

for x in waveformAlpha:
    print(f'The value of x is {x}')
    if(x != ''):
        print(float(x))
        waveformNumeric.append(float(x))
        

#  Create Numpy array:
        
waveformArray = np.array(waveformNumeric)

plt.plot(waveformArray)
plt.xlim(0, 150.0)