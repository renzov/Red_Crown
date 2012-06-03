#include<cstdio>
#include<cstring>
#include<cctype>
#include<cstdlib>
#include<climits>
#include<vector>
#include<string>
#include<set>
#include<queue>
#include<list>
#include<stack>
#include<map>
#include<algorithm>
#include<numeric>
#include<sstream>
#include<iostream>
using namespace std;
int x[205];
int y[205];

int main(){
  
  int n;
  cin >> n;
  int res = 0;
  for ( int i=0; i < n; ++i ){
	 cin >> x[i] >> y[i];
  }
  bool u,d,l,r;
  for ( int i=0; i < n; ++i ){
	 u = l = r = d = false;
	 for ( int j=0; j < n; ++j ){
		if ( i != j ){
		  if ( y[i] == y[j] && x[i] < x[j] ) r=true;
		  if ( y[i] == y[j] && x[i] > x[j] ) l=true;
		  if ( x[i] == x[j] && y[i] < y[j] ) u=true;
		  if ( x[i] == x[j] && y[i] > y[j] ) d=true;
		}
	 }
	 if ( u && d && l && r ) res++;
  }
  cout << res << endl;
  return 0;
}