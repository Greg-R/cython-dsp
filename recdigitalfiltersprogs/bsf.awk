#! /usr/bin/awk -f
# bsf.awk implements bsf.c as an awk script.
# Example:
#   brownrv 1000 0 0.5 13 | bsf.awk -v s=1000 -v f=20 -v b=10
#   which produces the same output as running the c program bsf like so:
#   brownrv 1000 0 0.5 13 | bsf 1000 20 10
#
#                            COPYRIGHT
#
#  bsf.awk
#  Copyright (C) 2014 Exstrom Laboratories LLC
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  A copy of the GNU General Public License is available on the internet at:
#  http://www.gnu.org/copyleft/gpl.html
#
#  or you can write to:
#
#  The Free Software Foundation, Inc.
#  675 Mass Ave
#  Cambridge, MA 02139, USA
#
#  Exstrom Laboratories LLC contact:
#  stefan(AT)exstrom.com
#
#  Exstrom Laboratories LLC
#  Longmont, CO 80503, USA
#
#

BEGIN{
    pi = atan2(0.0,-1.0) # pi = arctan(0/-1) = 3.141592653589793
    t = 2.0*pi*f/s
    r = 1.0-2.0*pi*b/s
    d1 = 2.0*cos(t)
    d1r = d1*r
    r2 = r*r
    printf("r=%lf\n", r) > "/dev/stderr"
}

{
    a0 = d1r*a1 - r2*a2 + $1
    printf("%lf\n",a0 - d1*a1 + a2)
    a2 = a1
    a1 = a0
}
