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

int N,C;
const int MAXN = 505;

vector< pii > G[ MAXN ];
vector< int > color[ MAXN ];

bool bridge[ MAXN ];
int num[MAXN];
int low[MAXN];
int deg[MAXN];
int p[MAXN];
int nc;
int O[5];
bool vis[MAXN];
int n;

void init(){
	for (int i=0; i < C; ++i){ 
		G[i].clear(); 
		deg[i] = 0; 
		p[i] = i; 
		vis[i] = false;
	}
	for (int i=0; i < N; ++i){ 
		color[i].clear(); 
		bridge[i] = false;
	}
	nc = C;
	n = 0;
}

int find_set( int x ){
	return ( x != p[x] )? ( p[x] = find_set(p[x]) ):x;
}

void link( int x , int y ){
	x = find_set(x);
	y = find_set(y);
	if ( x != y ){
		p[y] = x;
		nc--;
	}
}

void dfs( int u , int e ){
	vis[ u ] = true;
	num[ u ] = low[ u ] = n++;
	int t,v;
	for ( int i=0; i < G[u].size(); ++i ){
		t = G[u][i].first;
		if ( t != e ){
			v =	G[u][i].second;
			if ( !vis[ v ] ){
				dfs( v , t );
				if ( num[u] < low[v] ) bridge[ t ] = true;
				low[ u ] = min( low[u] , low[v]  );
			}
			else {
				low[ u ] = min( low[u] , num[v] );
			}
		}
	}
}

int get_res( int u ){
	int r = INT_MAX;
	for ( int i=0; i < G[u].size(); ++i )
		if ( !bridge[ G[u][i].first ] )
			r = min( r , G[u][i].first );
	
	if ( r == INT_MAX ){
		for ( int i=0; i < G[u].size(); ++i )
			r = min( r , G[u][i].first );
	}
	return r;
}

int main(){
	int k,u,v;
	while ( scanf("%d %d",&N,&C) && (N || C) ){

		init();

		for ( int i=0; i < C; ++i ){
			scanf("%d",&k);
			for ( int j=0; j < k; ++j ){
				scanf("%d",&u);
				color[u].push_back(i);
			}
		}
		//create graph
		for ( int i=0; i < N; ++i ){
			if ( color[i].size() == 2 ){
				u = color[i][0]; v = color[i][1];
				G[u].push_back( make_pair( i , v ) );
				deg[ u ]++;
				G[v].push_back( make_pair( i , u ) );
				deg[ v ]++;
				link( u , v );
			}
			else {
				u = color[i][0];
				deg[u] += 2;
				G[u].push_back( make_pair( i , u ) );
			}
		}
		//testing parity
		int odd = 0;
		int zeros = 0;
		for ( int i=0; i < C ; ++i ){
			if ( (deg[i] & 1) && odd < 3 ){
				O[odd] = i;
				odd++;
			}
			if ( deg[i] == 0 ) zeros++;
		}

		if ( odd > 2 || (nc-zeros) > 1 ){ puts("-1"); continue; }
		
		for ( int i=0; i < C; ++i )
			if ( deg[i] ){
				dfs( i , -1  );
				break;
			}
		
		int tmp;
		int e;
		int res = INT_MAX;

		if ( odd ){
			for ( int i=0; i < 2; ++i )
				res = min( res , get_res( O[i] ) );
		}
		else {
			res = 0;
		}
		printf("%d\n",res);
	}
	return 0;
}
