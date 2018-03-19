#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/*
 *                            COPYRIGHT
 *
 *  bsfb.c
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

// Compile: gcc -lm -o bsfb bsfb.c

int main( int argc, char *argv[] )
{
  if(argc < 4)
  {
      printf("Usage: %s s b f1 f2 ...\n", argv[0]);
      printf("Applies a bandstop filter bank to x[n] read from stdin.\n");
      printf("  s = sampling frequency\n");
      printf("  b = half power bandwidth\n");
      printf("  fi = stop frequencies\n");
      return(-1);
  }

  double s = strtod(argv[1], NULL);
  double b = strtod(argv[2], NULL);
  double r = 1.0-2.0*M_PI*b/s;
  double r2 = r*r;
  double f, t;
  int i, nf = argc - 3;
  double *d1 = (double *)malloc(nf*sizeof(double));
  double *d1r = (double *)malloc(nf*sizeof(double));

  for(i=0; i<nf; ++i){
    f = strtod(argv[3+i], NULL);
    t = 2.0*M_PI*f/s;
    d1[i] = 2.0*cos(t);
    d1r[i] = d1[i]*r;}

  double x;
  double *a0 = (double *)calloc(nf, sizeof(double));
  double *a1 = (double *)calloc(nf, sizeof(double));
  double *a2 = (double *)calloc(nf, sizeof(double));

  while(scanf("%lf", &x)!=EOF){
    for(i=0; i<nf; ++i){
      a0[i] = d1r[i]*a1[i] - r2*a2[i] + x;
      x = a0[i] - d1[i]*a1[i] + a2[i];
      a2[i] = a1[i];
      a1[i] = a0[i];}
    printf("%lf\n", x);}

  return(0);
}
