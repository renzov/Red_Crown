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

const int MAXN = 500005;

map<int,int> idx;
map<int,int> inv;
int N = 0; 
int dfsnum[MAXN];
int num = 0;
vector<int> G[MAXN];
int sumdeg;
int vertex;
int visited[MAXN];
int maxVal;

int get_idx( const int &x ){
	if ( idx.count(x) == 0 ){
		idx[x] = N;
		inv[N] = x;
		return N++;
	}
	else {
		return idx[x];
	}
}

void dfs( const int &u ){
	visited[vertex++] = u;
	dfsnum[u] = num++;
	maxVal = max( maxVal , inv[u] );
	int v;
	for ( int i = 0; i < (int)G[u].size(); ++i  ){
		sumdeg++;
		v = G[u][i];
		if ( dfsnum[v] == -1 ) dfs(v);
	}
}

int main(){
	int n;
	int x, y;
	int u, v;
	scanf("%d", &n);

	for ( int i=0; i < n; ++i ){
		scanf("%d %d", &x, &y);
		u = get_idx(x);
		v = get_idx(y);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	fill( dfsnum, dfsnum + N, -1 );
	
	long long res = 0;
	int edges;
	for ( int i=0; i < N; ++i ){
		if (  dfsnum[i] == -1 ){
			sumdeg = 0;
			vertex = 0;
			maxVal = 0;
			dfs( i );
			edges = sumdeg >> 1;
			for ( int j=0; j < vertex; ++j ){
				x = visited[j];
				y = inv[x];
				res += ( (int)G[x].size() - 1 )*(long long)y;
			}
			if ( edges < vertex ) res += maxVal;
		}
	}
	printf("%lld\n", res);
	return 0;
}

