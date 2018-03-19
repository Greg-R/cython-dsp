#! /usr/bin/awk -f
# bpf.awk implements bpf.c as an awk script.
# Example:
#   brownrv 1000 0 0.5 13 | bpf.awk -v s=1000 -v f=20 -v b=10
#   which produces the same output as running the c program bpf like so:
#   brownrv 1000 0 0.5 13 | bpf 1000 20 10
#
#                            COPYRIGHT
#
#  bpf.awk
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
    printf("r=%lf\n", r) > "/dev/stderr"
    A = (1.0-r)*sqrt(1.0-2.0*r*cos(2.0*t)+r*r)/(2.0*sin(t))
    t = 2.0*r*cos(t) # reuse t and r variables for use in the loop
    r = r*r
}

{
    a0 = t*a1 - r*a2 + $1
    printf("%lf\n",A*(a0 - a2))
    a2 = a1
    a1 = a0
}
