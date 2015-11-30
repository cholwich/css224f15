#include<stdio.h>
#include<stdlib.h>
#include<immintrin.h>
#include<x86intrin.h>

#define ALIGN __attribute__ ((aligned (32)))

int main() {
  double ALIGN A[] = {10,5,9,4,1,6,9,2};
  __m256d a,b,c,d,e,f,g;

  //How should we do if the length of A is 100?
  /*
  a = _mm256_load_pd(A);
  for(i=4; i<100; i+=4) {
    b = _mm256_load_pd(A+i);
    a = _mm256_max_pd(a, b);
  }
  c = a;
  */
  
  //Load the 1st 4 elements into a
  a = _mm256_load_pd(A); //[10,5,9,4]
  //Load the next 4 elements into b
  b = _mm256_load_pd(A+4); //[1,6,9,2]
  //Find the max between a and b
  c = _mm256_max_pd(a, b); //[10,6,9,4]
  //Use permute to change the element pos
  d = _mm256_permute2f128_pd(c, c, 1);
  // d = [9,4,10,6]
  e = _mm256_max_pd(c, d); //[10,6,10,6]
  //Use permute to change the positions
  f = _mm256_permute_pd(e, 5);
  g = _mm256_max_pd(e, f); //[10,10,10,10]
  //Store the values to the array
  _mm256_store_pd(A, g);
  printf("Max = %lf\n", A[0]);
}
