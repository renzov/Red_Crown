#include<cstdio>
#include<iostream>
#include<cstring>
#include<cctype>
#include<string>
#include<algorithm>
#include<cmath>
#include<queue>
#include<vector>
#include<stack>
#include<set>
#include<map>
#include<list>
#include<climits>
using namespace std;
#define forn(i,n) for ( int i=0; i < (int)(n); ++i )

int main(){
  
  int x,n,y;
  cin >> n >> x >> y;
  int A =  y*n - 100*x;
  int res;
  if ( A % 100 ){
	 res = (A / 100) + 1;
  }
  else {
	 res = A / 100;
  }
  cout << max(res,0) << endl;
  return 0;
}