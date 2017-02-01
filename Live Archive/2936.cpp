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

const int MAXN = 205;

int N,M;

vector<int> G[2][MAXN];
int size[MAXN * 2][ 2 ];
bool vis[2][MAXN];

void clean(){
	for ( int i=0; i < N; ++i ){
		G[0][i].clear();
		G[1][i].clear();
		vis[0][i] = vis[1][i] = false;
	}
}

pii dfs( int p , int u ){
	vis[p][u] = true;

	int v;
	pii res;
	pii tmp;
	res.first = res.second = 0;

	for ( int i = 0; i < G[p][u].size(); ++i ){
		v = G[p][u][i];
		if ( !vis[1-p][v] ){
			tmp = dfs( 1 - p , v );
			res.first += tmp.first;
			res.second += tmp.second;
		}
	}
	if ( p == 0 )
		res.first++;
	else 
		res.second++;
	return res;
}


int main(){
	int x,y;
	int runs;
	pii res;
	int tam;
	int c;

	scanf("%d",&runs);
	while ( runs-- ){
		scanf("%d %d",&N,&M);
		clean();
		while ( M-- ){
			scanf("%d %d",&x,&y);
			x--,y--;
			G[0][x].push_back(y);
			G[1][y].push_back(x);
		}
		c = 0;
		for ( int i=0; i < N; ++i ){
			for ( int j=0; j < 2; ++j ){
				if ( !vis[j][i] ){
					res = dfs( j , i );
					size[c][0] = res.first;
					size[c][1] = res.second;
					c++;
				}
			}
		}
		M = N >> 1;

		bool dp[M + 2][M + 2];
		memset( dp , false , sizeof(dp) );

		dp[0][0] = true;

		for ( int k =  0; k < c && !dp[M][M]; ++k ){
			if ( size[k][0] > M || size[k][1] > M ) continue;
			for ( int i = M - size[k][0]; i >= 0; i-- ){
				for ( int j = M - size[k][1]; j >= 0; j-- ){
					if ( dp[i][j] ){
						dp[ i + size[k][0] ][ j + size[k][1] ] = true;
					}
				}
			}
		}
		tam = M;
		while ( !dp[tam][tam] ) tam--;
		printf("%d\n",tam);
	}
	return 0;
}

