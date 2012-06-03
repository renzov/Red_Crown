#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
#include<vector>
#include<list>
#include<queue>
#include<stack>
#include<set>
#include<map>
#include<algorithm>
#include<numeric>
#include<string>
#include<iostream>
using namespace std;

#define forn(i,n) for(int i=0; i < (int)(n); ++i)
#define forab(i,a,b) forab(int i=(int)(a); i<(int)(b); ++i) 

int main(){
  
  int n;
  int x;
  cin >> n >> x;
  vector<int> a(n);
  forn(i,n) cin >> a[i]; 
  sort( a.begin() , a.end() );
  if ( a[(n+1)/2 - 1] == x ) cout << 0 << endl;
  else {
	 int res = 0;
	 while ( a[ (n+1)/2 - 1] != x ){
		a.push_back( x );
		sort( a.begin(), a.end() );
		res++;
		n++;
		//cout << a[ (n+1)/2 - 1 ] << endl;
	 }
	 cout << res << endl;
  }
  return 0;
}