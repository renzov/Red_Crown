#include<iostream>
using namespace std;

inline int abs(int x){ return x<0? -x:x; }

int main(){
  int a[25];
  int n;
  bool zeros;
  int cases = 0;
  int f;
  while (cin >> n && n){
	 cases++;
	 for (int i=0; i < n; ++i) cin >> a[i];
	 int res = 0;
	 while ( 1 ){
		zeros = true;
		f = a[0];
		for ( int i=0; i < n-1; ++i ){
		  a[i] = abs(a[i] - a[i+1]);
		  if ( a[i] ) zeros = false;
		}
		a[n-1] = abs(a[n-1] - f);
		if ( a[n-1] ) zeros = false;
		if ( !zeros ) res++;
		else break;
		if ( res > 1000 ) break;
	 }
	 cout << "Case "<< cases <<": ";
	 if ( zeros ) cout << res << " iterations" << endl;
	 else cout << "not attained" << endl;
  }
  return 0;
}