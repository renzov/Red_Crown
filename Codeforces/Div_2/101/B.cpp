#include<iostream>
using namespace std;
int main(){
  int left,right;
  int a,x,y;

  cin >> a >> x >> y;
  if ( a % 2 == 0 ){
	 left = -a/2;
	 right = a/2;
  }
  else {
	 left = -( a + 1 )/2;
	 right = (a+1)/2;
  }
  if ( (y % a == 0) ){ cout << -1 << endl; return 0; }
  int len = ( y / a );
  if ( len < 1 ){
	 if ( x > left && x < right ){
		cout << 1 << endl;
	 }
	 else  cout << -1 << endl;
  }
  else {
	 if ( len % 2 ){
		if ( x > left && x < right ){
		  cout << 2 + (len/2)*3 << endl;
		}
		else  cout << -1 << endl;
	 }
	 else {
		if (x==0){ cout << -1 << endl; return 0; }
		if ( x > -a && x < a ){
		  if ( x < 0 ){
			 cout << 3*(len/2) << endl;
		  }
		  else {
			 cout << 3*(len/2) + 1 << endl;
		  }
		}
		else cout << -1 << endl;
	 }
  }
  

  return 0;
}