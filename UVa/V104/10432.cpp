#include<cstdio>
#include<cmath>
const double PI = 2*acos(0);
int main(){

  int n;
  double r;
  double A;
  while ( scanf("%lf %d",&r,&n) != EOF ){
	 A = ((n*r*r)*sin( 2*PI / n ))/2;
	 A = floor( A*1000 + .5 )/1000;
	 printf("%0.3lf\n",A);
  }

  return 0;
}