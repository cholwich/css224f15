#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<immintrin.h>
#include<x86intrin.h>

#define ALIGN __attribute__ ((aligned (32)))

int main() {
  int i;
  double pi;
  double ALIGN A[] = {1,2,3,4};
  double ALIGN B[] = {1,1,1,1};
  double ALIGN C[] = {4,4,4,4};
  double ALIGN S[] = {0,0,0,0};
  __m256d a,b,c,s;

  a = _mm256_load_pd(A);
  b = _mm256_load_pd(B);
  c = _mm256_load_pd(C);
  s = _mm256_load_pd(S);

  for(i=1; i<=25000000; i++) {
    __m256d d = _mm256_mul_pd(a, a);
    // d = [1*1, 2*2, 3*3, 4*4]
    __m256d e = _mm256_div_pd(b, d);
    // e = [1/(1*1), 1/(2*2), 1/(3*3), 1/(4*4)]
    s = _mm256_add_pd(s, e);
    a = _mm256_add_pd(a, c);
    // a = [5, 6, 7, 8]
  }

  // s = [s1,s2,s3,s4]
  {
    __m256d t = _mm256_permute2f128_pd(s, s, 1);
    s = _mm256_add_pd(s, t);
    // s = [s1+s3, s2+s4, s1+s3, s2+s4]
    t = _mm256_permute_pd(s, 5);
    s = _mm256_add_pd(s, t);
    // s = [s1+s2+s3+s4, ....]
    _mm256_store_pd(S, s);
    pi = sqrt(6*S[0]);
    printf("Pi = %.15lf\n", pi);
  }
}
