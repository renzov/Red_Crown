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
#include <cassert>
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
typedef pair< int , int > edge;
typedef pair< int, int > pii;
typedef pair< int, pii > event;
const int MAXN = 10005;

map<edge, int> W;
map<edge, int> inv;
vector<int> G[MAXN];
vector<int> C[MAXN];
bool inPath[MAXN];
edge E[MAXN];
int V[MAXN];
int d[MAXN];
int rep[MAXN];
int N, M, K;
event Ev[2*MAXN];
set<pii>::iterator pnt[MAXN];

void dijkstra(){
	int u, v, w, we;
	edge e;
	priority_queue< pii, vector<pii>, greater<pii> > q;
	fill( rep, rep + N, -1 );
	fill( d, d + N, INT_MAX );
	u = V[K-1];
	rep[u] = K - 1;
	d[u] = 0;
	q.push( pii( 0 , u ) );
	for ( int i=K-2; i >= 0; --i ){
		v = V[i];
		e.first = min(u,v), e.second = max(u,v);
		inPath[ inv[e] ] = true;
		d[v] = d[u] + W[e];
		u = v;
		rep[u] = i;
		q.push( pii(d[u], u) );
	}
	while ( !q.empty() ){
		u = q.top().second;
		w = q.top().first;
		q.pop();
		if ( w > d[u] ) continue;
		for ( int i=0; i < (int) G[u].size(); ++i ){
			v = G[u][i];
			we = C[u][i];
			if ( w + we < d[v] ){
				d[v] = w + we;
				rep[v] = rep[u];
				q.push( pii( d[v], v ) );
			}
		}
	}
}

set<pii> S;

int main(){
	int runs;
	int u, v, w;
	edge e;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d", &N, &M);
		for ( int i=0; i < M; ++i ){
			scanf("%d %d %d", &u, &v, &w);
			if ( u > v ) swap(u, v);
			e.first = u, e.second = v;
			if ( W.find(e) == W.end() ){
				W[e] = w;
			}
			else if ( w < W[e] ){
				W[e] = w;
			}
		}
		
		M = 0;
		
		for ( map<edge,int>::iterator it=W.begin(); it != W.end(); it++ ){
			w = it->second;
			u = it->first.first;
			v = it->first.second;
			G[u].push_back(v), C[u].push_back(w);
			G[v].push_back(u), C[v].push_back(w);
			E[M] = it->first;
			inv[ it->first ] = M;
			inPath[M++] = false;
		}
		
		scanf("%d", &K);
		for ( int i=0; i < K; ++i ) scanf("%d", V+i);
		dijkstra();
		int ru, rv, m = 0;
		for ( int i=0; i < M; ++i ){
			if ( !inPath[i] ){
				u = E[i].first, v = E[i].second;
				ru = rep[u], rv = rep[v];
				if ( ru == -1 || rv == -1 || ru == rv ) continue;
				if ( ru > rv ) swap( ru , rv );
				Ev[m++] = event( ru , pii( -1, i ) );
				Ev[m++] = event( rv, pii( 1, i ) );
			}
		}
		sort( Ev, Ev + m );
		int j = 0;
		int len = 0;
		int idx;
		int res = 0;
		int d1, d2, d3;
		for ( int i=0; i < K-1; ++i ){
			while ( j < m && Ev[j].first == i ){
				idx = Ev[j].second.second;
				if ( Ev[j].second.first < 0 ){ //insertion
					w = W[ E[idx] ];
					u = E[idx].first, v = E[idx].second;
					ru = V[rep[u]], rv = V[rep[v]];
					d1 = d[u] - d[ru];
					d2 = d[v] - d[rv];
					d3 = min( d[ru], d[rv] );
					pnt[idx] = S.insert( pii (d1 + d2 + d3 + w - len, idx) ).first;
				}
				else {
					S.erase( pnt[idx] );
				}
				j++;
			}
			if ( !S.empty() ) 
				res = max( res , S.rbegin()->first + len + d[ V[0] ] - d[ V[i] ] );
			else 
				res = INT_MAX;
			len += d[ V[i] ] - d[ V[i+1] ];
		}
	
		if ( res < INT_MAX ) printf("%d\n", res);
		else puts("-1");
	
		if ( runs ){
			inv.clear();
			W.clear();
			S.clear();
			for ( int i=0; i < N; ++i ) C[i].clear(), G[i].clear();
		}
	}
	return 0;
}

