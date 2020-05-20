#include <stdlib.h>
#include <stdio.h>
#include "utilities.h"



int main(int argc, char *argv[])
{

  FILE *test;
  int imax, jmax;
  double **data;

  printf("File: %s\n",argv[1]);

  if(argc !=2) {
      printf("Usage: ./print-2d ./test.dat \n");
      exit(1);
  }

  if ((test = fopen(argv[1],"r")) == NULL){
       printf("Usage: ./print-2d ./test.dat \n");
       exit(1);
   }

  fread(&jmax, sizeof(int), 1, test);
  fread(&imax, sizeof(int), 1, test);


  printf("Array is a %d x %d matrix\n", jmax, imax);

  malloc2D(&data, jmax, imax);


  printf("I:%d  J:%d\n", imax, jmax);
  printf("-------------------------------------\n");

  fread(data[0], sizeof(double), (imax*jmax), test);

  print2D(data, jmax, imax);

  // close file
  fclose (test);

}
