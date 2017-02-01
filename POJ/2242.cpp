#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;
const double PI = 3.141592653589793;

int main(){
  double x1,y1,x2,y2,x3,y3;
  double a,b,c,s;
  double A;
  double R;
  while ( cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 ){
	 a = hypot( x1 - x2, y1 - y2 );
	 b = hypot( x1 - x3, y1 - y3 );
	 c = hypot( x2 - x3, y2 - y3 );
	 s = (a + b + c)/2;
	 A = sqrt(s*(s-a)*(s-b)*(s-c));
	 R = (a * b * c) / (4 * A);
	 cout << fixed << setprecision(2);
	 cout << 2 * PI * R << endl;
  }
  return 0;
}