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
const int WHITE = 0;
const int BLACK = 1;
const int GRAY = 2;

vector<int> G[1005];
int color[1005];
int b,w;
bool ok;

void dfs( int u , int c ){
	
	color[u] = c;

	if ( c == WHITE ) w++;
	else b++;

	int v;
	for ( int i=0; ok && i < G[u].size(); ++i ){
		v = G[u][i];
		if ( color[v] == GRAY ) dfs( v , 1 - c );
		else if ( color[v] == color[u] ){
			ok = false;
		}
	}
}

int main(){
	int m,n;
	int u,v;
	while ( scanf("%d %d",&n,&m) != EOF ){
		//Init
		for ( int i=0; i<n; ++i ){ G[i].clear(); color[i] = GRAY; }
		ok = true;
		while ( m-- ){
			scanf("%d %d",&u,&v);
			u--,v--;
			if ( u==v ) ok = false;
			else { G[u].push_back(v); G[v].push_back(u); }
		}
		int res = 0;
		for ( int i=0; ok && i < n; ++i ){
			if ( color[i] == GRAY ){
				b = 0;
				w = 0;
				dfs( i , BLACK );
				res += min( b , w );
			}
		}
		if ( ok ) printf("%d\n",res);
		else puts("Impossible");
	}
	return 0;
}

