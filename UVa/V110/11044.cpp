#include<iostream>
using namespace std;

int main(){

  int runs;
  int n,m;
  int r,l;
  cin >> runs;
  while (runs--){
	 cin >> n >> m;
	 n-=2; m-=2;
	 l = ( n / 3 ) + ( n%3 != 0 );
	 r = ( m / 3 ) + ( m%3 != 0 );
	 cout << l*r << endl;
  }

  return 0;
}