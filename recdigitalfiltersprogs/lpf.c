#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/*
 *                            COPYRIGHT
 *
 *  lpf.c
 *  Copyright (C) 2014 Exstrom Laboratories LLC
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  A copy of the GNU General Public License is available on the internet at:
 *  http://www.gnu.org/copyleft/gpl.html
 *
 *  or you can write to:
 *
 *  The Free Software Foundation, Inc.
 *  675 Mass Ave
 *  Cambridge, MA 02139, USA
 *
 *  Exstrom Laboratories LLC contact:
 *  stefan(AT)exstrom.com
 *
 *  Exstrom Laboratories LLC
 *  Longmont, CO 80503, USA
 *
 */

// Compile: gcc -lm -o lpf lpf.c

int main( int argc, char *argv[] )
{
  if(argc < 3)
  {
      printf("Usage: %s s f\n", argv[0]);
      printf("Applies a lowpass filter to x[n] read from stdin.\n");
      printf("  s = sampling frequency\n");
      printf("  f = half power frequency < s/2\n");
      return(-1);
  }

  double s = strtod(argv[1], NULL);
  double f = strtod(argv[2], NULL);
  double t = 2.0*M_PI*f/s;
  double r = (1.0-sin(t))/cos(t);
  double A = (1.0 - r)/2.0;
  double x;
  double a0, a1;

  a0 = a1 = 0.0;
  while(scanf("%lf", &x)!=EOF){
    a0 = r*a1 + x;
    printf("%lf\n", A*(a0 + a1));
    a1 = a0;
  }

  return(0);
}
