#include <cstdio>
#include <algorithm>
#include <set>
#include <climits>
#include <cassert>
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;
const int MAXN = 30005;
const int MAXE = 2 * MAXN;

int N,M;
int res;
int head[MAXN];
int nxt[MAXE];
int to[MAXE];
int len[MAXE];
int dmg[MAXE];
int E;

int D[MAXN];
int L[MAXN];

struct path {
	int len;
	int dmg;
	int vertex;

	path(){}
	path( int l, int d, int v ){
		len = l, dmg = d, vertex = v;
	}
	bool operator <(const path &that) const {
		int d1 = dmg + D[vertex];
		int d2 = that.dmg + D[ that.vertex ];
		if ( d1 != d2 ) return d1 < d2;
		return (len + L[vertex]) < (that.len + L[that.vertex]);
	}
};

set<path> S[MAXN];

void add_edge(int u, int v, int l, int d){
	to[E] = v, len[E] = l, dmg[E] = d, nxt[E] = head[u], head[u] = E, E++;
	to[E] = u, len[E] = l, dmg[E] = d, nxt[E] = head[v], head[v] = E, E++; 
}

void insert_path( int l, int d, int v ){ // insert in S[v] a path of lenght l and damage d
	//Remove suboptimal paths from S[v]
	if (S[v].empty()){
		S[v].insert( path( l , d, v ) );
		return;
	}
	set<path>::iterator it = S[v].upper_bound( path( -INT_MAX , d , v ) );
	set<path>::iterator elim;
	set<path>::iterator prev = it; 
	if ( prev != S[v].begin() ){ 
		--prev;
		// prev->dmg < d
		if ( prev->len >= l ) return; //no need to insert
	}
	if ( it->dmg == d && it->len >= l ){
		return; // No need to insert
	}
	else {
		// it->dmg >= d
		while ( it != S[v].end() && it->len <= l ){
			elim = it;
			it++;
			S[v].erase(elim);
		}
	}
	S[v].insert( path( l , d, v ) );
}

void merge( int u , int v ){
	set<path>::iterator it = S[v].begin();
	set<path>::iterator best;

	while ( it != S[v].end() ){
		//update res
		best = S[u].upper_bound( path( INT_MAX ,  M - it->dmg - D[it->vertex] , N ) );
		if ( best != S[u].begin() ){
			best--;
			res = max( res , (it->len + L[it->vertex]) + ( best->len + L[best->vertex] ) );
		}
		it++;
	}
	it = S[v].begin();
	while ( it != S[v].end() ){
		insert_path( it->len + L[it->vertex] - L[u] , it->dmg + D[it->vertex] - D[u] , u );
		it++;
	}
}

void dfs( int u , int p ){
	int v;
	set<path>::iterator it;
	int last = -1;

	for ( int e = head[u]; e > -1; e = nxt[e] ){
		v = to[e];
		if ( v == p ) continue;
		dfs( v , u );
		it = S[v].upper_bound( path( INT_MAX , M - dmg[e] , N ) );
		if ( it != S[v].end() ){	// Delete all unusable paths
			S[v].erase( it , S[v].end() );
		}
		L[v] += len[e], D[v] += dmg[e];
		// update of answer
		if ( !S[v].empty() ){
			if ( res < (L[v] + S[v].rbegin()->len) ) res = L[v] + S[v].rbegin()->len;
		}
		//Merge children
		if ( last == -1 ){ 
			last = v;
		}
		else {
			if ( (int)S[last].size() >= (int) S[v].size() )
				merge( last , v );
			else {
				merge( v , last );
				last = v;
			}
		}
	}
	if ( last == -1 ){ //Its a leaf
		S[u].insert( path(0,0,u) ); 
	}
	else {
		L[u] = L[last];
		D[u] = D[last];
		for ( it = S[last].begin(); it != S[last].end() ; it++ ){
			S[u].insert( path( it->len , it->dmg , u ) );
		}
		insert_path( -L[u], -D[u], u );
	}
}

int main(){
	int cases = 0;
	int runs;
	int u,v;
	int a,l;
	scanf("%d", &runs);
	while ( runs-- ){
		cases++;
		scanf("%d %d", &N, &M);
		assert( N > 0 && N < MAXN );
		E = 0;		
		for ( int i=0; i < N; ++i ){ head[i] = -1, L[i] = D[i] = 0; S[i].clear(); }
		L[N] = D[N] = 0;
		for ( int i=1; i < N; ++i ){
			scanf("%d %d %d %d", &u, &v, &a, &l);
			u--,v--;
			add_edge( u , v , l , a );
		}
		res = 0;
		dfs(0, -1);
		printf("Case %d: %d\n", cases, res);
	}
	return 0;
}

