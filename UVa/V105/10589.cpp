#include<cstdio>
#include<cmath>
#include<algorithm>
#include<string>
#include<iostream>
using namespace std;
const double EPS = 1e-10;
double cx[4];
double cy[4];

int main(){
  int n;
  long long a;
  double A;
  int m;
  double x,y;
  bool ok;
  double d;
  long long num;
  while ( scanf("%d %lld",&n,&a) && n ){
	 m = 0;
	 A = a;
	 cx[3] = cx[0] = 0; cx[2] = cx[1] = A;
	 cy[0] = cy[1] = 0; cy[2] = cy[3] = A;
	 for ( int i=0; i < n; ++i ){
		scanf("%lf %lf",&x,&y);
		ok = true;
		for ( int j=0; j < 4 && ok; ++j ){
		  d = hypot( x - cx[j] , y - cy[j] );
		  if ( (fabs( d - A ) > EPS) && d > A ) ok = false; 
		}
		if ( ok ) m++;
	 }
	 num = a * a * m;
	 string number = "";
	 char c;
	 for ( int i=10; i <= n; i*=10 ){
		c = (char)((num%10) + '0');
		number += c;
		num /= 10;
	 }
	 if ( number.size() > 5 ){
		number = number.substr(0,5);
	 }
	 int left = 5 - number.size();
	 number += '.';
	 if ( num ){
		while ( num ){
		  c = (char)((num%10) + '0');
		  num /= 10;
		  number += c;
		}
	 }
	 else {
		number += '0';
	 }
	 reverse( number.begin() , number.end() );
	 while ( left-- ) number += '0';
	 cout << number << endl;
  }
  return 0;
}