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
int N;

vector<int> G[MAXN];
int ds[MAXN];
int dt[MAXN];
int dr[MAXN];
int ordS[MAXN];
int ordT[MAXN];
int ordR[MAXN];
bool isMin[MAXN];
int vmin[MAXN];

void bfs( int s, int d[], int ord[] ){
	queue<int> q;
	fill( d, d + N, -1 );

	d[s] = 0;
	q.push( s );

	int u, v;
	int n;

	while ( !q.empty() ){
		u = q.front(); q.pop();
		ord[n++] = u;
		for ( int i=0; i < (int)G[u].size(); ++i ){
			v = G[u][i];
			if ( d[v] == -1 ){
				d[v] = d[u] + 1;
				q.push(v);
			}
		}
	}
	
}

int main(){
	int u, v;
	int s, t, r;
	int M;

	scanf("%d %d", &N, &M);
	while (M--){
		scanf("%d %d", &u, &v);
		u--, v--;
		G[u].push_back(v), G[v].push_back(u);
	}
	scanf("%d %d %d", &s, &t, &r);
	s--, t--, r--;
	bfs( s, ds, ordS );
	bfs( t, dt, ordT );
	bfs( r, dr, ordR );

	int res = 0;
	/* Determine the vertices that minimize the value
	   along some path from s to t 
	*/	

	printf("%d\n", res);
	return 0;
}

