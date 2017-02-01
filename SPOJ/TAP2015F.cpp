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

const int MAXN = 54321;
const int MAXE = 60;

int N, E;
vector<int> T[MAXN];
int D[MAXE][MAXE];
int col[MAXN];
int seen[MAXN][MAXE];
int dp[MAXN][MAXE];
int t = 0;

int dfs( int u, int c, int p ){
	if ( seen[u][c] == t ) return dp[u][c];
	seen[u][c] = t;
	int &res = dp[u][c];
	res = 0;
	int v;
	for ( int i=0; i < T[u].size(); ++i ){
		v = T[u][i];
		if ( v != p ){
			if ( col[v] != -1 ){
				res += ( D[c][col[v]] + dfs(v, col[v], u) );
			}
			else {
				int tmp = INT_MAX;
				for ( int f=0; f < E; ++f ){
					tmp = min( tmp, D[c][f] + dfs(v, f, u) );
				}
				res += tmp;
			}
		}
	}
	return res;
}

int main(){
	int k;
	int u, v;
	while ( scanf("%d %d", &N, &E) != EOF ){
		
		for (int i=0; i < N; ++i){
			T[i].clear();
			col[i] = -1;
		}
		
		for ( int i=0; i < E; ++i )
			for ( int j=0; j < E; ++j )
				scanf("%d", &D[i][j]);

		for ( int i=0; i < E; ++i ){
			scanf("%d", &k);
			while ( k-- ){
				scanf("%d", &u);
				u--;
				col[u] = i;
			}
		}
		
		for ( int i=1; i < N; ++i ){
			scanf("%d %d", &u, &v);
			u--, v--;
			T[u].push_back(v); T[v].push_back(u);
		}
		
		t++;
		if ( col[0] != -1 ){
			printf("%d\n", dfs(0, col[0], -1));
		}
		else {
			int res = INT_MAX;
			for ( int i=0; i < E; ++i ){
				res = min( res, dfs(0, i, -1) );
			}
			printf("%d\n", res);
		}
	}
	return 0;
}

