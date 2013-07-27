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

const int MAX = 70;
int N,K;
vector< int > T[MAX];
vector< int > C[MAX];
int dp[MAX][MAX][2];

inline int max3( int A, int B , int C ){
	return max( A , max( B , C ) );
}

void add( int u , int v, int w ){
	T[u].push_back(v);
	T[v].push_back(u);

	C[u].push_back(w);
	C[v].push_back(w);
}

void dfs( int u, int p ){

	if ( T[u].size() == 1 && p != -1 ){ // Its a leaf
		for ( int i=0; i <= K; ++i ){
			dp[u][i][0] = dp[u][i][1] = 0;
		}
		return;
	}

	int v;
	
	for ( int i=0; i < T[u].size(); ++i ){
		v = T[u][i];
		if ( v != p )
			dfs( v , u );
	}
	
	int best[2][MAX][MAX];
	int x = 1;
	int w;

	for ( int j=0; j <= K; ++j ){
		best[0][j][0] = 0;
		best[0][j][1] = -INT_MAX;
		best[0][j][2] = -INT_MAX;
	}
	//Knapsack
	for ( int i=0; i < T[u].size(); ++i ){
		
		v = T[u][i];
		w = C[u][i];

		if ( v == p ) continue;
		
		for ( int j=0; j <= K; ++j ){

			best[x][j][0] = best[1-x][j][0];
			best[x][j][1] = best[1-x][j][1];
			best[x][j][2] = best[1-x][j][2];

			if ( j > 0 ){
				best[x][j][0] = max( best[x][j][0] , best[x][j-1][0] );
				best[x][j][1] = max( best[x][j][1] , best[x][j-1][1] );
				best[x][j][2] = max( best[x][j][2] , best[x][j-1][2] );
			}

			for ( int t=0; t <= j; ++t ){

				best[x][j][0] = max( best[x][j][0] , best[1-x][j-t][0] + dp[v][t][0] );
				
				best[x][j][1] = max( best[x][j][1] , best[1-x][j-t][0] + dp[v][t][1] + w );

				if ( best[1-x][j-t][1] != -INT_MAX ) 
					best[x][j][1] = max( best[x][j][1] , best[1-x][j-t][1] + dp[v][t][0] );

				if ( best[1-x][j-t][1] != -INT_MAX )
					best[x][j][2] = max( best[x][j][2] , best[1-x][j-t][1] + dp[v][t][1] + w );

				if ( best[1-x][j-t][2] != -INT_MAX )
					best[x][j][2] = max( best[x][j][2] , best[1-x][j-t][2] + dp[v][t][0] );


			}

		}
		x = 1 - x;
	}

	x = 1 - x;

	dp[u][0][0] = 0;
	dp[u][0][1] = max( best[x][0][1] , best[x][0][0] );

	for ( int j=1; j <= K ; ++j ){
		dp[u][j][0] = max( max( best[x][j][0] , best[x][j-1][1]) , max( dp[u][j-1][0] , best[x][j-1][2] ) );
		dp[u][j][1] = max3( dp[u][j-1][1] ,  best[x][j][0] , best[x][j][1] );
	}

}

int main(){

	int runs;
	int u,v,w;
	
	scanf("%d",&runs);
	while ( runs-- ){
		
		scanf("%d %d",&N,&K);

		for ( int i=0; i<N; ++i ){
			T[i].clear(); C[i].clear();
		}

		for ( int i=0; i < (N-1); ++i ){
			scanf("%d %d %d",&u,&v,&w);
			u--,v--;
			add( u , v , w );
		}
		
		dfs( 0 , -1 );

		printf("%d\n",dp[0][K][0]);
	
	}
	return 0;
}

