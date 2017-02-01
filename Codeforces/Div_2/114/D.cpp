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
const double EPS = 1e-8;
int n,l,k;
double p[ 205 ];
int a[205];
double dp[2][205][205] = {0};


int main(){
  int x;
  int next;
  cin >> n >> l >> k;
  forn(i,n){ cin >> p[i]; p[i]/=100;  }
  forn(i,n) cin >> a[i];
  k = min( l , k );
  dp[0][0][k] = 1.0;
  x = 0;
  forn(i,n){
	 for ( int j=0; j <= n; ++j ){
		for ( int K=0; K <= l; ++K ){
		  if ( fabs( dp[x][j][K] ) > EPS ){
			 //Ganar
			 if ( a[i] == -1 ){
				dp[1-x][j+1][K] += dp[x][j][K] * p[i];
			 }
			 else {
				next = min( l , K + a[i] );
				dp[1-x][j+1][next] += dp[x][j][K] * p[i];
			 }
			 //Peder
			 dp[1-x][j][K] += dp[x][j][K]*(1-p[i]);
		  }
		}
	 }
	 x = 1 - x;
  }
  double res = 0.0;
  for ( int j=l; j <= n; ++j ){
	 res += dp[x][j][l];
  }
  printf("%lf\n",res);
  return 0;
}