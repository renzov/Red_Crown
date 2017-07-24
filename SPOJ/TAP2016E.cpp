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
#define x first
#define y second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

const int MAXN = 1024;

int N, M;
int T[MAXN*10];
int tm = 0; 
vector<pii> G[MAXN][MAXN];
int vis[MAXN][MAXN] = {0};

inline int get( const int &i, const int &j ){
	return T[ i*M + j ];
}

inline int idx( const int &i, const int &j ){
	return i*M + j;
}

void dfs( const int &x, const int &y ){
	if ( vis[x][y] >= tm ) return;
	vis[x][y] = tm;
	pii s;
	for ( int i=0; i < (int)G[x][y].size(); ++i ){
		s = G[x][y][i];
		if ( vis[s.x][s.y] < tm ) dfs( s.x, s.y );
	}
}


int main(){
	
	while ( scanf("%d %d", &N, &M) != EOF ){
		tm++;

		for ( int i=0; i < N; ++i ){
			for ( int j=0; j < M; ++j ){
				scanf("%d", &T[ idx(i,j) ] );
				T[ idx(i,j) ]--;
			}
		}
		// Create the graph
		for ( int i=0; i < N; ++i )
			for ( int j = 0; j < N; ++j )
				for ( int a=0; a < M; ++a)
						G[ get(i,a) ][ get(j,a) ].push_back( pii( i , j ) );

		// Do dfs
		dfs(0,0);
		bool ok = true;
		for ( int i=0; i < N && ok; ++i )
			for ( int j=0; j < N && ok; ++j )
				if ( vis[i][j] < tm ) ok = false;

		if (ok) puts("S");
		else puts("N");

		for ( int i=0; i < N; ++i )
			for ( int j=0; j < N; ++j )
				G[i][j].clear();

	}
	return 0;
}

