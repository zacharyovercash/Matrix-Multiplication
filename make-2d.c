#include <stdlib.h>
#include <stdio.h>
#include "utilities.h"


int main(int argc, char *argv[])
{
   FILE *test2;
   int i;
   double **x;

   if(argc !=4) {
       printf("Usage: <./make-2d> <Rows> <Columns> <Output file> \n");
       exit(1);
   }

   if ((test2 = fopen(argv[3],"wb")) == NULL){
     printf("Usage: <./make-2d> <Rows> <Columns> <Output file> \n");
     exit(1);
    }
   //test2 = fopen("test2.dat","wb");

    for(i=0; i<argc; i++) {
        printf("%s, ", argv[i]);
    } printf("\n");

    int imax= atoi(argv[2]);
    int jmax= atoi(argv[1]);

    malloc2D(&x, jmax,imax);


    fwrite(&jmax,sizeof(int),1,test2);
    fwrite(&imax,sizeof(int),1,test2);

    //fill2D(x, jmax, imax);
    //initHeat2D(x, jmax, imax);
    fill2DRand(x, jmax, imax);


    fwrite(x[0],sizeof(double),jmax*imax,test2);

    print2D(x, jmax, imax);

    exit(0);

}
