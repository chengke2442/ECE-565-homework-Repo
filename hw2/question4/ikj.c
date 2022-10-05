#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

const int stride = 16;
int num_elements;
int num_traversals;

double A[1024][1024];
double B[1024][1024];
double C[1024][1024]; 

double calc_time(struct timespec start, struct timespec end) {
  double start_sec = (double)start.tv_sec*1000000000.0 + (double)start.tv_nsec;
  double end_sec = (double)end.tv_sec*1000000000.0 + (double)end.tv_nsec;
  if (end_sec < start_sec) {
    return 0;
  } else {
    return end_sec - start_sec;
  }
}

void init_array() {
  for (uint64_t i = 0;i<1024;i++)
    {
      for (int j = 0;j<1024;j++)
	{
	  A[i][j] = 2;
	}
    }

  for (int i = 0;i<1024;i++)
    {
      for (uint64_t j = 0;j<1024;j++)
	{
	  B[i][j] = 4;
	  
	}
    }

  for (int i = 0;i<1024;i++)
    {
      for (int j = 0;j<1024;j++)
	{
	  C[i][j] = 0;
	}
    }
  
}

double ijk_tiling(){
  uint64_t i,j,k;
  uint64_t ii,jj,kk;
  double sum;
  uint64_t block_size =64;
  struct timespec start_time,end_time;
  clock_gettime(CLOCK_MONOTONIC, &start_time);
  for (i = 0;i<1024;i+=block_size)
    {
      for (j = 0;j<1024;j+=block_size)
	{
	  for (k = 0;k<1024;k+=block_size)
	    {
	  for (ii = i;ii<i+block_size;ii++)
	    {
	      for (jj = j;jj<j+block_size;jj++)
		{
		      for (kk = k;kk<k+block_size;kk++)
			{
			  
			  // sum+=A[ii][kk] * B[kk][jj];
			   C[ii][jj] +=A[ii][kk]*B[kk][jj];
			}
       		    }
		 
		}
	    }
	    
	}
    }


  clock_gettime(CLOCK_MONOTONIC,&end_time);
  double e = calc_time(start_time,end_time);
  return e;
}
double ijk()
{
  uint64_t i,j,k;
  double sum;
  struct timespec start_time, end_time;  
    clock_gettime(CLOCK_MONOTONIC, &start_time);
  // i - j - k
  for (i=0; i<1024; i++) {
    for (j = 0;j<1024;j++)
    {
      sum = 0;
      for (k = 0;k<1024;k++)
	{
	  sum+=A[i][k]*B[k][j];
	}
      C[i][j] = sum;
    }
    }
clock_gettime(CLOCK_MONOTONIC, &end_time);

  double elapsed_ns = calc_time(start_time, end_time);
  return elapsed_ns;
}


double ikj()
{
 uint64_t i,j,k;
  double sum;
  struct timespec start_time, end_time;  
    clock_gettime(CLOCK_MONOTONIC, &start_time);
  // i - j - k
  for (k = 0;k<1024;k++)
    {
      for ( i = 0;i<1024;i++)
	{
	  sum = A[i][k];
	  for (j = 0;j<1024;j++)
	    {
	       C[i][j] += sum * B[k][j];
	    }
	  
	}
    }
clock_gettime(CLOCK_MONOTONIC, &end_time);

  double elapsed_ns = calc_time(start_time, end_time);
  return elapsed_ns;
}

double jki()
{
  uint64_t i,j,k;
  double sum;
  struct timespec start_time, end_time;  
    clock_gettime(CLOCK_MONOTONIC, &start_time);
  for (j = 0;j<1024;j++)
    {
      for(k = 0;k<1024;k++)
	{
	  sum = B[k][j];
	  for (i = 0;i<1024;i++)
	    {
	      C[i][j] += sum * A[i][k]; 
	    }
	}
    }
clock_gettime(CLOCK_MONOTONIC, &end_time);

  double elapsed_ns = calc_time(start_time, end_time);
  return elapsed_ns;
}


int main(int argc, char *argv[]) {

  uint64_t index = 0;
  struct timespec start_time, end_time;
 
 
  num_elements = 1024;
  int x = atoi(argv[1]); 
   
  init_array();

  //int i,j,k;
  //uint64_t sum;
  //  clock_gettime(CLOCK_MONOTONIC, &start_time);
  // i - j - k
  /* for (i=0; i<1024; i++) {
    for (int j = 0;j<1024;j++)
    {
      sum = 0;
      for (int k = 0;k<1024;k++)
	{
	  sum+=A[i][k]*B[i][k];
	}
      C[i][j] = sum;
    }
    }*/


  // i - k - j
  /* for (int i = 0;i<1024;i++)
    {
      for (int k = 0;k<1024;k++)
	{
	  sum = A[i][k];
	  for (int j = 0;j<1024;j++)
	    {
	       C[i][j] += sum * B[k][j];
	    }
	  
	}
    }
  */

  // j - k - i
  /*  for (int j = 0;j<1024;j++)
    {
      for(int k = 0;k<1024;k++)
	{
	  sum = B[k][j];
	  for (int i = 0;i<1024;i++)
	    {
	      C[i][j] += sum * A[i][k]; 
	    }
	}
	}*/
  // clock_gettime(CLOCK_MONOTONIC, &end_time);

  // double elapsed_ns = calc_time(start_time, end_time);
  if (x == 1){
    printf("Time for i-j-k = %f\n", ijk()/1000000000);
  }
  else if (x == 2){
    printf("Time for i-k-j = %f\n", ikj()/1000000000);
  } else if (x == 3){
     printf("Time for j-k-i = %f\n",jki()/1000000000);
   }
  else if (x == 4){
     printf("Time for ijk_tiling = %f\n",ijk_tiling()/1000000000); 
   }
  //  printf("NS per load = %f\n", (elapsed_ns / ((uint64_t)num_elements * (uint64_t)num_traversals * 16)));
  // printf("end index = %lu\n", index);

  //  free();
  return 0;
}
