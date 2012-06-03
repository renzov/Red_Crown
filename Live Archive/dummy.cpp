#include<iostream>
using namespace std;
int main(){

  for ( int x = 2; x <= 31; ++x )
	 for ( int y=1; y < x; ++y )
		if (160 == ( 4*(x-1) + 10*(y-1) + (31-x)*20 )) cout << x << " " << y << endl;

  return 0;
}