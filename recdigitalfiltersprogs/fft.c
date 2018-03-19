#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/*
 *                            COPYRIGHT
 *
 *  fft.c
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

// Compile: gcc -lm -o fft fft.c

void FFT( double *c, int N, int isign );

int main( int argc, char *argv[] )
{
  if(argc < 2)
  {
    printf("Usage: fft n\n");
    printf("Calculates the FFT of the first n points read from stdin.\n");
    printf("If number of points read < n then zeros are added.\n");
    return(-1);
  }

  int np = atoi(argv[1]);
  double *c = (double *)malloc( 2 * np * sizeof(double) );
  int i = 0;

  while(scanf("%lf", &(c[2*i]))!=EOF && i<np){
    c[2*i+1]=0.0;
    ++i;}

  for(; i<np; ++i){
    c[2*i]=0.0;
    c[2*i+1]=0.0;}

  FFT( c, np, 1 );

  for( i = 0; i < np; ++i )
  {
    printf("%lf %lf\n", c[2*i], c[2*i+1] );
  }

  free( c );
}

/**********************************************************************
  FFT - calculates the discrete fourier transform of an array of double
  precision complex numbers using the FFT algorithm.

  c = pointer to an array of size 2*N that contains the real and
    imaginary parts of the complex numbers. The even numbered indices contain
    the real parts and the odd numbered indices contain the imaginary parts.
      c[2*k] = real part of kth data point.
      c[2*k+1] = imaginary part of kth data point.
  N = number of data points. The array, c, should contain 2*N elements
  isign = 1 for forward FFT, -1 for inverse FFT.
*/

void FFT( double *c, int N, int isign )
{
  int n, n2, nb, j, k, i0, i1;
  double wr, wi, wrk, wik;
  double d, dr, di, d0r, d0i, d1r, d1i;
  double *cp;

  j = 0;
  n2 = N / 2;
  for( k = 0; k < N; ++k )
  {
    if( k < j )
    {
      i0 = k << 1;
      i1 = j << 1;
      dr = c[i0];
      di = c[i0+1];
      c[i0] = c[i1];
      c[i0+1] = c[i1+1];
      c[i1] = dr;
      c[i1+1] = di;
    }
    n = N >> 1;
    while( (n >= 2) && (j >= n) )
    {
      j -= n;
	  n = n >> 1;
    }
    j += n;
  }

  for( n = 2; n <= N; n = n << 1 )
  {
    wr = cos( 2.0 * M_PI / n );
    wi = sin( 2.0 * M_PI / n );
    if( isign == 1 ) wi = -wi;
    cp = c;
    nb = N / n;
    n2 = n >> 1;
    for( j = 0; j < nb; ++j )
    {
      wrk = 1.0;
      wik = 0.0;
      for( k = 0; k < n2; ++k )
      {
        i0 = k << 1;
        i1 = i0 + n;
        d0r = cp[i0];
        d0i = cp[i0+1];
        d1r = cp[i1];
        d1i = cp[i1+1];
        dr = wrk * d1r - wik * d1i;
        di = wrk * d1i + wik * d1r;
        cp[i0] = d0r + dr;
        cp[i0+1] = d0i + di;
        cp[i1] = d0r - dr;
        cp[i1+1] = d0i - di;
        d = wrk;
        wrk = wr * wrk - wi * wik;
        wik = wr * wik + wi * d;
      }
      cp += n << 1;
    }
  }
}
