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
const int MAXN = 100005;

vector<int> T[MAXN];
int d[MAXN] = {0};
bool dead[MAXN];

void dfs( int u, int p ){
	d[u] = ( dead[p] )? (d[p]+1):d[p];
	int v;
	for ( int i=0; i < T[u].size(); ++i ){
		v = T[u][i];
		if ( v != p )
			dfs( v , u );
	}
}

int main(){
	int N, M;
	int u, v;
	int runs;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &N);
		for( int i=1; i <= N; ++i ){ T[i].clear(); dead[i] = false; d[i] = 0; }
		for ( int i=1; i < N; ++i ){
			scanf("%d %d", &u, &v);
			T[u].push_back(v);
			T[v].push_back(u);
		}
		scanf("%d", &M);
		while ( M-- ){
			scanf("%d", &u);
			dead[u] = true;
		}
		dfs(1, 0);
		double res = 0.0;
		for ( int i=1; i <= N; ++i ){
			res += d[i]*1.0/(d[i]+1);
		}
		printf("%.6f\n", res);
	}
	return 0;
}

