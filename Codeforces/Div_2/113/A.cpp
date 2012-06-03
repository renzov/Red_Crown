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

pair<int,int> a[ 100 ];

int main(){
  
  int n,k;
  cin >> n >> k;
	forn(i,n){
		cin >> a[i].first >> a[i].second;
	  a[i].first *= -1;
	}
	sort( a, a + n );
	int res = 1;
	for (int i=0; i < (k-1); ++i) if ( a[i] == a[k-1] ) res++;
	for (int i=k; i < n; ++i) if ( a[i] == a[k-1] ) res++;
	cout << res << endl;
  return 0;
}