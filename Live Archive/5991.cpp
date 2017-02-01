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
typedef pair< int , int > pii;

const int MAXN = 70005;
int N;
int L[MAXN];
int R[MAXN];
vector<int> T[MAXN];
set< pii > S[MAXN];
int res[MAXN];
int d[MAXN];
int rep[MAXN];

void insert_vert( int u, int v ){
	set<pii>::iterator it2, e;
	it2 = S[u].lower_bound( pii( L[v], INT_MAX ) );
	if ( it2 != S[u].begin() ) { 
		it2--;
		if ( it2->second >= d[v] ) return;
		it2++;
	}
	while ( it2 != S[u].end() && it2->second <= d[v] ){
		e = it2++;
		S[u].erase( e );
	}
	S[u].insert( pii(L[v], d[v]) );
}

void merge( int u, int v ){
	set<pii>::iterator it2, e;
	for ( set<pii>::iterator it=S[v].begin(); it != S[v].end(); ++it ){
		it2 = S[u].lower_bound( pii( it->first, INT_MAX ) );
		if ( it2 != S[u].begin() ) { 
			it2--;
			if ( it2->second >= it->second ) continue;
			it2++;
		}
		while ( it2 != S[u].end() && it2->second <= it->second ){
			e = it2++;
			S[u].erase( e );
		}
		S[u].insert( *it );
	}
}

void dfs( int u ){
	if ( (int) T[u].size() == 0 ){ // leaf 
		res[u] = 0;
		rep[u] = u;
		S[u].insert( pii( L[u] , d[u] ) );
		return;
	}
	int last = -1;
	int v;
	for ( int i=0; i < T[u].size(); ++i ){
		v = T[u][i];
		d[v] = d[u] + 1;
		dfs( v );
		if ( last == -1 ) { 
			last = rep[v];
		}
		else {
			v = rep[v];
			if ( S[last].size() >= S[v].size() ){
				merge( last , v );
			}
			else {
				merge ( v, last );
				last = v;
			}
		}
	}
	// query 
	set<pii>::iterator it = S[last].lower_bound( pii( R[u] , INT_MAX ) );
	if ( it == S[last].begin() ){ 
		res[u] = 0;
	}
	else {
		it--;
		res[u] = it->second - d[u];
	}
	insert_vert( last, u );
	rep[u] = last;
}

int main(){
	int runs;
	int u;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &N);
		for ( int v=0; v < N; ++v ){
			scanf("%d %d %d", &u, L+v, R+v);
			if ( u >= 0 ) T[u].push_back(v);
		}
		d[0] = 0;
		dfs( 0 );
		printf("%d", res[0]);
		for ( int i=1; i < N; ++i ) printf(" %d", res[i]);
		puts("");
		if ( runs ){	// Clean up memory for next testcase
			for ( int i=0; i < N; ++i ) T[i].clear(), S[i].clear();
		}
	}
	return 0;
}

