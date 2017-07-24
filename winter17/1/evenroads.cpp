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
typedef pair<int,int> pii;
typedef pair< int , pii > piii;

const int MAXN = 10005;

vector<int> G[MAXN];
vector<int> W[MAXN];
int d[MAXN][2];
int N, M;

int dijkstra(){
	// init distance matrix
	for ( int i=0; i < N; ++i ) d[i][0] = d[i][1] = INT_MAX;
	priority_queue< piii, vector<piii>, greater<piii> > q;
	d[0][0] = 0;
	q.push( piii(0 ,  pii(0,0)) );
	
	int u, v;
	int par, w;
	int nx;

	while ( !q.empty() ){
		w = q.top().first;
		u = q.top().second.first;
		par = q.top().second.second;
		q.pop();
		if ( w > d[u][par] ) continue;
		if ( u == (N-1) && par == 0 ) return d[u][par];
		nx = 1 - par;
		for ( int i=0; i < (int)G[u].size(); ++i ){
			v = G[u][i];
			if ( d[v][nx] > d[u][par] + W[u][i] ){
				d[v][nx] = d[u][par] + W[u][i];
				q.push( piii( d[v][nx], pii( v, nx ) ) );
			}
		}
	}
	return -1;
}

int main(){
	int u, v, w;
	scanf("%d %d", &N, &M);
	while ( M-- ){
		scanf("%d %d %d", &u, &v, &w);
		u--, v--;
		G[u].push_back(v);
		G[v].push_back(u);
		W[u].push_back(w);
		W[v].push_back(w);
	}
	printf("%d\n", dijkstra());
	return 0;
}

