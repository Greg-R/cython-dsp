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
#        print(float(x))
        waveformNumeric.append(float(x))
        

#  Create Numpy array:
        
waveformArray = np.array(waveformNumeric)

#plt.style.use('sineplotstyle')
#plt.plot(waveformArray)
#plt.xlim(0, 150.0)

from matplotlib.backends.backend_agg import FigureCanvasAgg as FigureCanvas
from matplotlib.figure import Figure

#plt.style.use('sineplotstyle')

#fig = Figure(figsize=(12,10))
fig = Figure()
# A canvas must be manually attached to the figure (pyplot would automatically
# do it).  This is done by instantiating the canvas with the figure as
# argument.
FigureCanvas(fig)
ax = fig.add_subplot(111)
#ax.plot([1, 2, 3])
ax.set_title('Waveform')
ax.grid(True, which='both')
ax.set_xlabel('time')
ax.set_ylabel('volts')
ax.plot(waveformArray)
ax.set_xlim(0,200)
ax.minorticks_on()
display(fig)

#import matplotlib.backends.backend_pdf.FigureCanvas

from matplotlib.backends.backend_pdf import PdfPages

with PdfPages('foo.pdf') as pdf:
     # As many times as you like, create a figure fig and save it:
 #    fig = plt.figure()
 #    pdf.savefig(fig)
     # When no figure is specified the current figure is saved
     pdf.savefig(fig)
     
import matplotlib as plt     
print(plt.get_configdir())