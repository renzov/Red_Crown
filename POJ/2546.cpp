#include<cstdio>
#include<cmath>
#include<algorithm>
#include<iostream>
#include<iomanip>
using namespace std;
const double PI = 3.141592654;
const double EPS = 1e-8;
double atanF(double b, double a ){
  if (fabs(b) < EPS) return  (PI / 2);
  return atan2(b,a);
}

int main(){
  double c1x,c1y;
  double c2x,c2y;
  double r1,r2;
  double d,s;
  scanf("%lf %lf %lf",&c1x,&c1y,&r1);
  scanf("%lf %lf %lf",&c2x,&c2y,&r2);
  d = hypot( c1x-c2x, c1y-c2y );
  s = r1 + r2;
  if ( r1 < r2 ) swap(r1,r2);
  if ( fabs( s - d ) < EPS || d > s ){
	 cout << fixed;
	 cout << setprecision (3) << 0.0 << endl;
	 return 0;
  }
  if ( fabs( r1 - d - r2 ) < EPS || r1 > ( r2 + d ) ){
	 cout << fixed;
	 cout << setprecision (3) << (r2*r2*PI) << endl;
	return 0;
  }
  // Caso general
  double a1 = ((r1*r1 - r2*r2)/d + d) * 0.5;
  double a2 = d - a1;
  double b = sqrt(r1*r1 - a1*a1);
  double A = (r1*r1)*atanF(b, a1) - a1*b;
  A = A + (r2*r2)*atanF(b, a2) - a2*b;
  cout << fixed;
  cout << setprecision (3) << A << endl;
  return 0;
} 