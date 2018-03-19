#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

// Compile: gcc -lm -o sines sines.c
// Input file format
// n (number of sines)
// a1 (amplitude) f1 (frequency) p1 (phase)
// a2             f2             p2
// an             fn             pn

double sumarray(int n, double *a)
{
  int i;
  double s = 0.0;

  for(i=0; i<n; ++i) s+=a[i];
  return(s);
}

//  Changed main to sinegen.
int sinegen( int argc, char *argv[] )
{
  if( argc != 4 )
  {
    printf("Usage: %s file s n\n", argv[0]);
    printf("Produces n samples of the sine waves defined in file.\n");
    printf("  s = sampling frequency\n");
    printf("Received arguments: %s %s %s %s\n", argv[0], argv[1], argv[2], argv[3]);
    exit( -1 );
  }

//printf("Received arguments: %s %s %s %s\n", argv[0], argv[1], argv[2], argv[3]);



//char * filePath = strcat("./recdigitalfiltersprogs/", argv[1]);

//printf("filePath = %s\n", filePath);

  FILE *fp = fopen(argv[1], "r");
  double s = strtod(argv[2], NULL);
  unsigned int is, ns = strtoul(argv[3], NULL, 10);
  int i, n, fscanfCheck;

  fscanfCheck = fscanf(fp, "%d", &n);

//printf("The value of n = %d\n", n);
//printf("The value of ns = %d\n", ns);

  double a, f, p, t;
  double *x = (double *)malloc(n*sizeof(double));
  double *y = (double *)malloc(n*sizeof(double));
  double *cs = (double *)malloc(n*sizeof(double));
  double *sn = (double *)malloc(n*sizeof(double));

  for(i=0; i<n; ++i){
    fscanfCheck = fscanf(fp, "%lf %lf %lf", &a, &f, &p);
 //   printf("Scanning: %lf %lf %lf \n", a, f, p);
    t = 2.0*M_PI*f/s;
    cs[i] = cos(t);
    sn[i] = sin(t);
    x[i] = a*cos(p);
    y[i] = a*sin(p);
    }

//if(fscanfCheck) printf("fscanf fail!\n");

  // y = samples of a*sin(2*pi*f*t + p)
  // x = samples of a*cos(2*pi*f*t + p)

//  printf("%lf\n", sumarray(n,y));
  for(is=1; is<ns; ++is){
    for(i=0; i<n; ++i){
    t = x[i];
    x[i] = cs[i]*x[i] - sn[i]*y[i];
    y[i] = sn[i]*t + cs[i]*y[i];
    }
    
    printf("%lf\n", sumarray(n,y));
}
  return( 0 );
}

