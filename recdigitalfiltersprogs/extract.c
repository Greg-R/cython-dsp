#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/*
 *                            COPYRIGHT
 *
 *  extract.c
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

// Compile: gcc -lm -o extract extract.c

int main( int argc, char *argv[] )
{
  if( argc < 2 )
    {
      printf("Usage: extract info\n");
      printf("  Extracts information from an fft file read from stdin\n");
      printf("  info = m for magnitude\n");
      printf("         p for phase\n");
      printf("         r for real part\n");    
      printf("         i for imaginary part\n");
      return(-1);
    }

  char info = argv[1][0];
  double x, y;

  while(scanf("%lf %lf", &x, &y)!=EOF)
    switch( info )
      {
      case 'm': 
	printf("%lf\n", sqrt(x*x + y*y));
	break;
      case 'p':
	printf("%lf\n", atan2(y,x));
	break;
      case 'r':
	printf("%lf\n", x);
	break;
      case 'i':
	printf("%lf\n", y);
	break;
      }

  return(0);
}
