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
typedef pair< int, int > pii;
typedef pair< int , int > edge;

const int MAXN = 5005;
vector<edge> E;
vector<int> W;
vector<int> ord;
int N, M;
set<pii> cut[MAXN];
int min_edge[MAXN];
int p[MAXN];
int size[MAXN];

bool cmp( const int &a, const int &b ){
	return W[a] > W[b];
}

inline int find_set( const int &x ){
	return ( x == p[x] )? x:( p[x] = find_set(p[x]) );
}

void join( const int &u, const int &v ){ // joint set v into set u
	p[v] = u;
	size[u] += size[v];
	min_edge[u] = min( min_edge[u], min_edge[v] );
	int a, b, idx;
	set<pii>::iterator it;
	for ( it = cut[v].begin(); it != cut[v].end(); it++ ){
		if ( cut[u].find( *it ) != cut[u].end() ){ // this edge is no more inside cut
			//printf("found edge %d inside cut\n", it->second);
			min_edge[u] = min( min_edge[u] , it->first );
			cut[u].erase( *it );
		}
		else {	// new edge inside the cut
			cut[u].insert( *it );
		}
	}
	cut[v].clear();
}

int main(){

	int runs;
	int u ,v, w;

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d", &N, &M);
		// set union
		for ( int i=0; i < N; ++i ) p[i] = i, min_edge[i] = INT_MAX, size[i] = 1;

		for ( int i=0; i < M; ++i ){
			scanf("%d %d %d", &u, &v, &w);
			u--, v--;
			if ( u > v ) swap(u,v);
			E.push_back( edge(u,v) );
			W.push_back( w );
			ord.push_back(i);
			cut[u].insert( pii(w, i) ), cut[v].insert( pii (w, i));
		}

		int res = 0;
		sort( ord.begin(), ord.end(), cmp );
		int idx;
		for ( int i=0; i < M; ++i ){
			idx = ord[i];
			u = E[idx].first, v = E[idx].second;
			u = find_set( u ), v = find_set( v );
			if ( u != v ){
				// do find union
				if ( cut[u].size() >= cut[v].size() ){
					//printf("join set %d into set %d\n", v, u);
					join( u , v );
					if ( cut[u].empty() || cut[u].rbegin()->first < min_edge[u] ){ 
						//if ( cut[u].empty() ) printf("cut empty\n");
						//else { printf("%d < %d\n",  cut[u].rbegin()->first, min_edge[u] ); }
						//printf("adding size %d\n", size[u]);
						res += size[u];
					}
				}
				else {
					//printf("join set %d into set %d\n", u, v);					
					join( v, u );
					if ( cut[v].empty() || cut[v].rbegin()->first < min_edge[v] ){ 
						//if ( cut[v].empty() ) printf("cut empty\n");
						//else { printf("%d < %d\n",  cut[v].rbegin()->first, min_edge[v] ); }
						//printf("adding size %d\n", size[v]);						
						res += size[v];		
					}
				}
			}
		}
		printf("%d\n", res);
		if ( runs ){
			E.clear(), W.clear(), ord.clear();
			for ( int i=0; i < N; ++i ) cut[i].clear();
		}
	}
	return 0;
}

