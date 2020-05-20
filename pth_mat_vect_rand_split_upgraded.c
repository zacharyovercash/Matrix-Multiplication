#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "utilities.h"
#include "timer.h"

#define BLOCK_LOW(id,p,n)  ((id)*(n)/(p))
#define BLOCK_HIGH(id,p,n) (BLOCK_LOW((id)+1,p,n)-1)
#define BLOCK_SIZE(id,p,n) \
                     (BLOCK_HIGH(id,p,n)-BLOCK_LOW(id,p,n)+1)

//Blakley Parker and Zach Overcash
//4/25/20
//Pthread - Matrix Multiplication

/* Global variables */
int thread_count;
int arows, acols, brows,bcols;
double** x;
double** y;
double** z;
double IOstart, IOfinish, IOtime, Multiply, Mstart, Mfinish, overall;

/* Parallel function */
void *Pth_mat_vect(void* rank);

/*------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
   long       thread;
   pthread_t* thread_handles;
   GET_TIME(IOstart);
   FILE *inFile;

   if(argc !=5) {
         printf("Usage: ./pth_mat_vect_rand_split_upgraded <threads> <matrix A.dat> <matrix B.dat> <output file.dat>\n");
         exit(1);
     }

   thread_count = strtol(argv[1], NULL, 10);


   if ((inFile = fopen(argv[2],"r")) == NULL){
        printf("Usage: ./pth_mat_vect_rand_split_upgraded <threads> <matrix A.dat> <matrix B.dat> <output file.dat>\n");
         exit(1);
     }

   //creation of first matrix
   fread(&arows, sizeof(int), 1, inFile);
   fread(&acols, sizeof(int), 1, inFile);
   malloc2D(&x,arows,acols);
   fread(x[0], sizeof(double), (arows*acols), inFile);
   fclose(inFile);

   //open second matrix file
   if ((inFile = fopen(argv[3],"r")) == NULL){
         printf("Usage: ./pth_mat_vect_rand_split_upgraded <threads> <matrix A.dat> <matrix B.dat> <output file.dat>\n");
         exit(1);
     }

   fread(&brows, sizeof(int), 1, inFile);
   fread(&bcols, sizeof(int), 1, inFile);

   //malloc second matrix
   malloc2D(&y,brows,bcols);

   //fill second matrix
   fread(y[0], sizeof(double), (brows*bcols), inFile);
   fclose(inFile);

   //malloc matrix to store multiplication
   malloc2D(&z,arows,bcols);

    //check that the matricies are compatable
    if(acols != brows)
    {
    printf("Cannot multiply these two matricies!");
    exit(1);
    }

   thread_handles = malloc(thread_count*sizeof(pthread_t));

   for (thread = 0; thread < thread_count; thread++)
      pthread_create(&thread_handles[thread], NULL,
         Pth_mat_vect, (void*) thread);

   for (thread = 0; thread < thread_count; thread++)
      pthread_join(thread_handles[thread], NULL);

#  ifdef DEBUG
      printf("---------------Matrix A---------------\n");
      print2D(x, arows, acols);
      printf("---------------Matrix B---------------\n");
      print2D(y, brows, bcols);
      printf("---------------Matrix C---------------\n");
      print2D(z, arows, bcols);
#  endif

      //open write file
    if ((inFile = fopen(argv[4],"w")) == NULL){
        printf("Usage: ./stencil-2d <num iterations> <input file> <final output> file doesnt exist\n");
        exit(1);
      }

    //write new matrix to file
    int size= arows*bcols;
    fwrite(&arows,sizeof(int),1,inFile);
    fwrite(&bcols,sizeof(int),1,inFile);
    double *newp=&(z[0][0]);
    fwrite(newp,sizeof(double),size,inFile);

    //IO finish time
    GET_TIME(IOfinish);

    IOtime=IOfinish-IOstart;
    overall=IOtime+Multiply;

    printf("num_threads\tm\tn\tToverall\tTcomputation\n");
    printf("%d\t\t%d\t%d\t%e\t%e\n",thread_count, arows, bcols, overall, Multiply);

   free(x);
   free(y);
   free(z);

   return 0;
}  /* main */

void *Pth_mat_vect(void* rank) {
   long my_rank = (long) rank;
   int i, j, k;
   int start_row = BLOCK_LOW(my_rank, thread_count, arows);
   int end_row = BLOCK_HIGH(my_rank,thread_count,arows);
   double temp;


   GET_TIME(Mstart);
   for (i = start_row; i <= end_row; i++) {
      for (j = 0; j < bcols; j++) {
          z[i][j] = 0.0;
          for(k = 0; k < acols; k++){
            temp = x[i][k]*y[k][j];
            z[i][j] += temp;
          }
      }
   }
   GET_TIME(Mfinish);
   Multiply=Mfinish-Mstart;
      return NULL;
}  /* Pth_mat_vect */
