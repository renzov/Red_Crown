#include<iostream>
using namespace std;
int main(){
  int  n;
  int a[10];
  cin >> n;
  for( int i=0; i < 7; ++i ){
	 cin >> a[i];
  }
  int i=0;
  while ( a[i] < n ){
	 n -= a[i];
	 i=(i+1)%7;
  }
  cout << i+1<< endl;
  return 0;
}