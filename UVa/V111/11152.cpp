#include<cstdio>
#include<cmath>
const double PI = 2 * acos(0);
const double EPS = 1e-8;
int main(){
  double a,b,c;
  double r,A,s,R;
  double sun,roses,viol;
  while ( scanf("%lf %lf %lf",&a,&b,&c) != EOF ){
	 s = ( a + b + c )/2;
	 A = sqrt( s*(s-a)*(s-b)*(s-c) );
	 r = A / s;
	 R = (a * b * c)/ ( 4 * A );
	 roses = PI * r * r;
	 viol = A - roses;
	 sun = R*R*PI - A;
	 printf("%0.4lf %0.4lf %0.4lf\n",sun,viol,roses);
  }
  return 0;
}