#include<cstdio>
#include<cmath>
const double EPS = 1e-8;
int main(){
  double a,b,c;
  double r,A,s;
  while ( scanf("%lf %lf %lf",&a,&b,&c) != EOF ){
	 s = ( a + b + c )/2;
	 A = sqrt( s*(s-a)*(s-b)*(s-c) );
	 if ( fabs(s) < EPS ) r = 0.0;
	 else r = A / s;
	 r = floor(r*1000 + .5)/1000;
	 printf("The radius of the round table is: %0.3lf\n",r);
  }
  return 0;
}