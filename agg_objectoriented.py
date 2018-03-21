#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Mar 19 20:49:15 2018

@author: raven
"""

#  100% Object Oriented!!!

from matplotlib.backends.backend_agg import FigureCanvasAgg as FigureCanvas
from matplotlib.figure import Figure

fig = Figure()
# A canvas must be manually attached to the figure (pyplot would automatically
# do it).  This is done by instantiating the canvas with the figure as
# argument.
FigureCanvas(fig)
ax = fig.add_subplot(111)
ax.plot([1, 2, 3])  # specify (nrows, ncols, axnum)
ax.set_title('Waveform')
ax.grid(True)
ax.set_xlabel('time')
ax.set_ylabel('volts')

display(fig)

#fig.savefig('test')