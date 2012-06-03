#include<iostream>
using namespace std;

int a[ 5005 ];
bool used[ 5005 ] = {0};

int main(){
  int n;
  int res = 0;
  cin >> n;

  for ( int i=0; i<n; ++i ){
	 cin >> a[i];
	 if ( a[i] > n ) res++;
	 else if ( used[ a[i] ] ) res++;
	 else used[ a[i] ] = true;
  }
  cout << res << endl;
}