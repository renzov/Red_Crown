#include<iostream>
using namespace std;

int f(int n){
  if ( n < 10 ) return n;
  int s = 0;
  while ( n ){
	 s += n%10;
	 n/=10;
  }
  return f(s);
}

int main(){
  int n;
  while ( cin >> n && n ){
	 cout << f(n) << endl;
  }
  return 0;
}