#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utilities.h"

void malloc2D(double*** a , int jmax, int imax)
{
   // first allocate a block of memory for the row pointers and the 2D array
   double **x = (double **)malloc(jmax*sizeof(double *) + jmax*imax*sizeof(double));

   // Now assign the start of the block of memory for the 2D array after the row pointers
   x[0] = (double *)x + jmax;

   // Last, assign the memory location to point to for each row pointer
   for (int j = 1; j < jmax; j++) {
      x[j] = x[j-1] + imax;
   }

    *a = x;
}

void fill2D(double** a, int jmax, int imax) {

    int count = 0.0;
    for(int j=0; j<jmax; j++) {
        for(int i=0; i<imax; i++) {
            a[j][i] = count;
            count++;
        }
    }
}

void fill2DRand(double** a, int jmax, int imax) {
    time_t t;
    srand48((unsigned)time(&t));
    int count = 0.0;
    for(int j=0; j<jmax; j++) {
        for(int i=0; i<imax; i++) {
            a[j][i] = 	drand48();
            count++;
        }
    }
}

void initHeat2D(double** a, int jmax, int imax) {

  printf("Intial Heat Map\n");
  printf("------------------------------------------------------------------------------\n");
    for(int j=0; j<jmax; j++) {
      a[j][0] = 1;
      a[j][imax-1]= 1;
    }
}

void print2D(double** a, int jmax, int imax) {

    for(int j=0; j<jmax; j++) {
        for(int i=0; i<imax; i++) {
            printf("%06.4lf\t", a[j][i]);
        } printf("\n");
    }
}

void multiplyMatrix(double**a, double **b,double **c, int n, int m,int r2)
{
	//initialize elements of c to 0
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			c[i][j]=0;
		}
	}

	//multiplying matrices
	for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < r2;k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}
