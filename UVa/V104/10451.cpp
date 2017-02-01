#include<cstdio>
#include<cmath>
const double PI = 2 * acos( 0 );
int main(){
  int n;
  double A;
  double a1,a2;
  double R,r;
  int runs = 0;
  while ( scanf("%d %lf",&n,&A) && ( n > 2 ) ){
	 // A = n*R*R*sin( 2*PI / n ) / 2
	 // R^2 = (2 * A) / n * sin ( 2*PI / n )
	 // r = R * cos ( PI / n )
	 runs++;
	 R =  sqrt ( (2 * A) / ( n * sin ( 2*PI / n ) ) );
	 r = R * cos( PI / n );
	 a1 = R*R*PI - A;
	 a2 = A - r*r*PI;
	 printf("Case %d: %0.5lf %0.5lf\n",runs,a1,a2);
  }

  return 0;
}