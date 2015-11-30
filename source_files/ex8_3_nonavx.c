//Without AVX
#include<stdio.h>
#include<math.h>

int main() {
  int i;
  double s, pi;

  s = 0.0;
  for(i=1; i<=100000000; i++) {
    s += 1.0/pow(i, 2);
  }
  //s = pi^2/6 ---> pi = sqrt(6*s)
  pi = sqrt(6*s);
  printf("Pi = %.15lf\n", pi);
}
