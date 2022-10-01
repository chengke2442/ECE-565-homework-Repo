#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

const int stride = 16;
int num_elements;
int num_traversals;

uint64_t A[1024][1024];
uint64_t B[1024][1024];
uint64_t C[1024][1024]; 

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
  for (int i = 0;i<1024;i++)
    {
      for (int j = 0;j<1024;j++)
	{
	  A[i][j] = i;
	}
    }

  for (int i = 0;i<1024;i++)
    {
      for (int j = 0;j<1024;j++)
	{
	  B[i][j] = j;
	  
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


int main(int argc, char *argv[]) {

  uint64_t index = 0;
  struct timespec start_time, end_time;
 
 
  num_elements = 1024;
  
   
  init_array();

  int i,j,k;
  uint64_t sum;
  clock_gettime(CLOCK_MONOTONIC, &start_time);
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


  // k - i - j
  /*  for (int k = 0;k<1024;k++)
    {
      for (int i = 0;i<1024;i++)
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
  for (int j = 0;j<1024;j++)
    {
      for(int k = 0;k<1024;k++)
	{
	  sum = B[k][j];
	  for (int i = 0;i<1024;i++)
	    {
	      C[i][j] += sum * A[i][k]; 
	    }
	}
    }
  clock_gettime(CLOCK_MONOTONIC, &end_time);

  double elapsed_ns = calc_time(start_time, end_time);
  printf("Time = %f\n", elapsed_ns);
  printf("NS per load = %f\n", (elapsed_ns / ((uint64_t)num_elements * (uint64_t)num_traversals * 16)));
  printf("end index = %lu\n", index);

  //  free();
  return 0;
}
