#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Mar 15 19:36:07 2018

@author: raven
"""

#  Import the DSP module which contains C functions.

import dsp_module

args = ["sines", "./recdigitalfiltersprogs/sines3.def", "2000", "1024"]
argsEncoded = [x.encode('UTF-8') for x in args]

#  The Wurlitzer allows stdio to be piped into Ipython.
from wurlitzer import sys_pipes, pipes
with sys_pipes():
    dsp_module.sine_gen(4, argsEncoded)

#  This context manager pushes stdio to the variable out.
#  This makes a giant string with \n delimiters.
    
with pipes() as (out, err):
    dsp_module.sine_gen(4, argsEncoded)

#  stdout is a giant string.
stdout = out.read()

#import matplotlib.pyplot as plt
#import numpy as np
#plt.plot(stdout)

#  Transform stdout into something that matplotlib can digest.

waveformAlpha = stdout.split('\n')

#  Create an array to dump the data into.
waveformNumeric = []

for x in waveformAlpha:
    print(f'The value of x is {x}')
    if(x != ''):
#        print(float(x))
        waveformNumeric.append(float(x))

#  The intent is to use a purely object oriented approach to plotting.

from matplotlib.backends.backend_agg import FigureCanvasAgg as FigureCanvas
from matplotlib.figure import Figure

#  Could not get default style sheet in ~/.config/matplotlib to work!
#  So use the local file:
plt.style.use('sineplotstyle')

#fig = Figure(figsize=(12,10))
fig = Figure()
# A canvas must be manually attached to the figure (pyplot would automatically
# do it).  This is done by instantiating the canvas with the figure as
# argument.
FigureCanvas(fig)
ax = fig.add_subplot(111)
ax.set_title('Waveform')
ax.grid(True, which='both')
ax.set_xlabel('time')
ax.set_ylabel('volts')
ax.plot(waveformNumeric)
ax.set_xlim(0,200)
ax.minorticks_on()
display(fig)

#  Save the figure to a PDF file.

from matplotlib.backends.backend_pdf import PdfPages

with PdfPages('foo.pdf') as pdf:
     # As many times as you like, create a figure fig and save it:
 #    fig = plt.figure()
 #    pdf.savefig(fig)
     # When no figure is specified the current figure is saved
     pdf.savefig(fig)

#  This configuration directory can hold a matplotlibrc
#  file.  Although it didn't work with the Anaconda installation.
#  This command left here for future reference.
     
#import matplotlib as plt     
#print(plt.get_configdir())