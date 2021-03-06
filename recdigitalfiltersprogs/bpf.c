#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/*
 *                            COPYRIGHT
 *
 *  bpf.c
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

// Compile: gcc -lm -o bpf bpf.c

int main( int argc, char *argv[] )
{
  if(argc < 4)
  {
      printf("Usage: %s s f b\n", argv[0]);
      printf("Applies a bandpass filter to x[n] read from stdin.\n");
      printf("  s = sampling frequency\n");
      printf("  f = center frequency\n");
      printf("  b = half power bandwidth\n");
      return(-1);
  }

  double s = strtod(argv[1], NULL);
  double f = strtod(argv[2], NULL);
  double b = strtod(argv[3], NULL);
  double t = 2.0*M_PI*f/s;
  double r = 1.0-2.0*M_PI*b/s;
  double A = (1.0-r)*sqrt(1.0-2.0*r*cos(2.0*t)+r*r)/(2.0*sin(t));
  double x;
  double a0, a1, a2;

  fprintf(stderr,"r=%lf\n", r);

  t = 2.0*r*cos(t);
  r = r*r;
  a0 = a1 = a2 = 0.0;
  while(scanf("%lf", &x)!=EOF){
    a0 = t*a1 - r*a2 + x;
    printf("%lf\n", A*(a0 - a2));
    a2 = a1;
    a1 = a0;
  }

  return(0);
}
