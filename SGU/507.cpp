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

const int MAXN = 50005;

int N, M;
int p[MAXN];
int indeg[MAXN];
int res[MAXN];
int rep[MAXN];
set<int> S[MAXN];

void join( const int &v, const int &u ){
	int x = rep[u], y = rep[v];
	if ( S[x].empty() ){ // First adding
		rep[u] = y;
		res[u] = res[v];
		return;
	}
	res[u] = min( res[u], res[v] );	
	set<int>::iterator gr, leq;
	if ( S[x].size() >= S[y].size() ){
		for ( set<int>::iterator it = S[y].begin(); it != S[y].end(); ++it ){
			leq = gr = S[x].upper_bound( *it );
			if ( leq == S[x].begin() ) leq = S[x].end();
			else leq--;
			if ( gr != S[x].end() ) res[u] = min( res[u], *gr - *it );
			if ( leq != S[x].end() ) res[u] = min( res[u], *it - *leq );
		}
		for ( set<int>::iterator it = S[y].begin(); it != S[y].end(); ++it ){
			S[x].insert( *it );
		}
		rep[u] = x;
	}
	else {
		for ( set<int>::iterator it = S[x].begin(); it != S[x].end(); ++it ){
			leq = gr = S[y].upper_bound( *it );
			if ( leq == S[y].begin() ) leq = S[y].end();
			else leq--;
			if ( gr != S[y].end() ) res[u] = min( res[u], *gr - *it );
			if ( leq != S[y].end() ) res[u] = min( res[u], *it - *leq );
		}
		for ( set<int>::iterator it=S[x].begin(); it != S[x].end(); ++it ){
			S[y].insert( *it );
		}
		rep[u] = y;
	}
}

int main(){
	int x;
	scanf("%d %d", &N, &M);
	rep[0] = 0;
	for ( int i=1; i < N; ++i ){ 
		scanf("%d", p+i);
		p[i]--;
		indeg[ p[i] ]++;
		rep[i] = i;
	}
	queue<int> q;
	int u, v;
	for ( v = N-M; v < N; ++v ){
		u = p[v];
		scanf("%d", &x);
		S[v].insert(x);	
		res[v] = INT_MAX;
		join( v, u );
		indeg[ u ]--;
		if ( indeg[u] == 0 ) q.push(u);
	}
	for ( int i=0; i < N-M-1; ++i ){
		v = q.front(); q.pop();
		u = p[v];
		join( v, u );
		indeg[u]--;
		if ( indeg[u] == 0 ) q.push(u);
	}
	for ( int i=0; i < N-M; ++i ){ 
		if (i) putchar(' ');
		printf("%d", res[i]);
	}
	puts("");
	return 0;
}

