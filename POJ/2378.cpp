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

const int MAXN = 10005;

int N;
int t;
int res[MAXN];
vector<int> G[MAXN];
int T[MAXN];

void dfs(int u, int p){
	int v;
	bool ok = true;
	T[u] = 1;
	for ( int i=0; i < G[u].size(); ++i ){
		v = G[u][i];
		if ( T[v] == -1 )
			dfs( v , u );
		if ( v != p ){ 
			ok &= ( 2*T[v] <= N );
			T[u] += T[v];
		}
	}
	if ( p != -1 ){
		ok &= (2*(N - T[u]) <= N);
	}
	if (ok) res[t++] = u + 1;
}

int main(){
	int u,v;
	scanf("%d",&N);
	for ( int i=1; i < N; ++i ){
		scanf("%d %d",&u,&v);
		u--,v--;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	fill( T , T + N , -1 );
	t = 0;
	dfs(0,-1);
	if (t == 0) puts("NONE");
	else {
		sort( res , res + t );
		for ( int i=0; i<t; ++i )
			printf("%d\n",res[i]);
	}
	return 0;
}
