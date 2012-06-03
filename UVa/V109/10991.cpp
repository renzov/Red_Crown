#include<cstdio>
#include<cmath>
const double PI = 2 * acos(0);

double get_angle( double a, double b, double c ){
  double cosine = (b*b + c*c - a*a) / (2*b*c);
  return acos(cosine);
}

int main(){
  double r1,r2,r3;
  double a,b,c,s,A;
  double a1,a2,a3;
  double theta1,theta2,theta3;
  int runs;
  scanf("%d",&runs);
  while ( runs-- ){
	 scanf("%lf %lf %lf",&r1,&r2,&r3);
	 a = r1 + r2;
	 b = r2 + r3;
	 c = r1 + r3;
	 s = (a + b + c)/2;
	 A = sqrt( s*(s-a)*(s-b)*(s-c) );
	 theta1 = get_angle( a , b , c );
	 theta2 = get_angle( b , a , c );
	 theta3 = get_angle( c , a , b );
	 a1 = 0.5*theta1*r3*r3;
	 a2 = 0.5*theta2*r1*r1;
	 a3 = 0.5*theta3*r2*r2;
	 printf("%0.6lf\n",A-a1-a2-a3);
  }
  return 0;
}