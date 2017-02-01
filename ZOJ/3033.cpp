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

const int MAXN = 500; // Max number of vertices
const int INF = 1 << 30;

vector< int > G[MAXN];
vector< int > C[MAXN];
int N;			// Number of vertices

bool in[MAXN];	// true if v is the queue, false otherwise
int y[MAXN];	// Potential vector (for distances)
int phi[MAXN];	// Number of times vertex v has been enqueued

bool bellman_ford( int s ){

	for ( int i=0; i < N; ++i ){
		y[i] = INF;
		in[i] = false;
		phi[i] = 0;
	}

	queue<int> q;
	int u,v,w;

	y[s] = 0;
	q.push( s );
	in[s] = true;
	phi[s]++;

	while ( !q.empty() ){
	
		u = q.front();
		q.pop();
		in[u] = false;
	
		if ( phi[u] >= N ) return false;

		for ( int i=0; i < G[u].size(); ++i ){
			v = G[u][i];
			w = C[u][i];
			if ( y[u] + w < y[v] ){
				y[v] = y[u] + w;
				if ( !in[v] ){
					q.push( v );
					phi[v]++;
				}
			}
		}
	}
	return true;
}


int main(){

	int runs;
	int s,e;
	int m;
	int u,v,w;

	scanf("%d",&runs);
	
	while (runs--){
		scanf("%d",&N);
		scanf("%d %d",&s,&e);
		
		for ( int i=0; i<N; ++i ){
			G[i].clear();
			C[i].clear();
		}

		scanf("%d",&m);
		while (m--){
			scanf("%d %d %d",&u,&v,&w);
			G[u].push_back(v);
			C[u].push_back(w);
		}

		if ( !bellman_ford(s) || y[e] == INF ) puts("infinity");
		else printf("%d\n",y[e]);
	}	
	return 0;
}
