#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <numeric>
#include <climits>

#define repn( i , a , b ) for( int i = ( int ) a ; i < ( int ) b ; i ++ )
#define rep( i , n ) repn( i , 0 , n ) 
#define all( x )  x.begin() , x.end()
#define rall( x ) x.rbegin() , x.rend()
#define mp make_pair
#define fst first
#define snd second
using namespace std;
typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;


int dp[45][20005];
int sol[45][20005];
int H[50];
int m;
int n;

void relax(int i,int j){
	int a = j + H[i];
	int b = j - H[i];
	int tmp;
	if ( a <= m ){
		tmp = max( a , dp[i][j] );
		if ( dp[i+1][a] > tmp ){
			dp[i+1][a] = tmp;
			sol[i+1][a] = -1;
		}
	}
	if ( b >= 0 ){
		if ( dp[i+1][b] > dp[i][j] ){
			dp[i+1][b] = dp[i][j];
			sol[i+1][b] = 1;
		}
	}
}

void solve(){
	rep(i,n+1)
		rep(j,m+1){
			dp[i][j] = INT_MAX;
		}
	dp[0][0] = 1;
	relax(0,0);
	repn(i,1,n){
		rep(j,m){
			if ( dp[i][j] != -1 ){
				relax(i,j);
			}
		}
	}
}

void printSol(int pos, int h){
	if ( pos == 0 ) return;
	int next = h + H[pos - 1]*sol[pos][h];
	printSol( pos - 1 , next );
	if ( sol[pos][h] > 0 ) putchar('D');
	else putchar('U');
}

int main(){
	int runs;
	scanf("%d",&runs);
	while ( runs-- ){
		scanf("%d",&n);
		rep(i,n){
			scanf("%d",H+i);
			m += H[i];
		}
		m >>= 1;
		solve();
		if ( dp[n][0] == INT_MAX ) printf("IMPOSSIBLE\n");
		else { printSol(n,0); putchar('\n'); }
	}
	return 0;
}

