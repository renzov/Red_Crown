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

const int MAXN = 105;
const int MAXT = 105;

int N, T, cases;
int done[MAXN][MAXT] = {0};
double dp[MAXN][MAXT];
int type[MAXN];

double solve( int pos, int t ){
	
	if ( t < 0 ) return 0.0;
	if ( t==0 ){
		return pos == N? 1.0:0.0;
	}
	if ( pos == N ) return 1.0;

	if (done[pos][t] == cases) return dp[pos][t];
	// Test every outcome
	double &res = dp[pos][t];
	res = 0.0;
	done[pos][t] = cases;
	int nxtp;
	for ( int dx = 1; dx <= 6; ++dx ){
		if ( (dx + pos) <= N ) nxtp = dx + pos;
		else nxtp = 2*N - pos - dx;
		if ( type[nxtp] == 1 ){
			res += solve( nxtp, t - 2 ) / 6.0;
		}
		else if ( type[nxtp] == 2 ){
			res += solve( 0 , t - 1 ) / 6.0;
		}
		else {
			res += solve( nxtp, t - 1 ) / 6.0;
		}
	}
	return res;
}

int main(){
	int L,B;
	int x;
	cases = 0;
	while ( scanf("%d %d %d %d", &N,&T,&L,&B) && N ){
		cases++;
		fill( type , type + N + 1, 0 );
		for ( int i=0; i < L; ++i ){
			scanf("%d", &x);
			type[x] = 1;
		}
		for (int i=0; i < B; ++i ){
			scanf("%d", &x);
			type[x] = 2;
		}
		printf("%0.6lf\n", solve(0, T));
	}
	return 0;
}

