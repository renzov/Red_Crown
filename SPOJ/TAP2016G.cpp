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
const int LOG = 31;
int N;
vector<int> G[MAXN];
vector<int> W[MAXN];
int d[MAXN];

// Trie
int M = 0; // Number of nodes
int endnode[MAXN*LOG];
int T[MAXN*LOG][2];
int bits;

void dfs( int u, int p ){
	int v;
	for ( int i=0; (int) i < G[u].size(); ++i){
		v = G[u][i];
		if ( v != p ){ 
			d[v] = d[u] ^ W[u][i];
			dfs( v, u );
		}
	}
}

int find_max_bits(){
	int res = 0;
	int t, num;
	for ( int i=0; i < N; ++i ){
		t = 0, num = d[i];
		while ( num ) num >>= 1, t++;
		res = max(res , t);
	}
	return res;
}

void insert( int idx ){
	int node = 0;
	for ( int i=bits-1; i >= 0; --i ){
		if ( ( d[idx] >> i ) & 1 ){
			if ( T[node][1] == -1 ){
				T[node][1] = ++M;
			}
			node = T[node][1];
		}
		else {
			if ( T[node][0] == -1 ) {
				T[node][0] = ++M;
			}
			node = T[node][0];
		}
	}
	endnode[node] = idx;
}

int query( int n ){
	int node = 0;
	for ( int i=bits-1; i >= 0; --i ){
		if ( ( n >> i ) & 1 ){
			if ( T[node][0] == -1 ){
				node = T[node][1];
			}
			else { 
				node = T[node][0];
			}
		}
		else {
			if ( T[node][1] == -1 ) {
				node = T[node][0];
			}
			else {
				node = T[node][1];
			}
		}
	}
	if ( endnode[node] == -1 ) while(1);
	return d[ endnode[node] ];
}

int main(){
	int u, v, w;

	for ( int i=0; i < (MAXN*LOG); ++i  ){
		T[i][0] = T[i][1] = -1;
		endnode[i] = -1;
	}

	while ( scanf("%d", &N) != EOF ){
		// Prepare memory
		for ( int i=0; i < N; ++i ) G[i].clear(), W[i].clear();
		for ( int i=0; i < M; ++i ){
			T[i][0] = T[i][1] = -1;
			endnode[i] = -1;
		}
		// Read the test cases 
		for ( int i=1; i < N; ++i ){
			scanf("%d %d %d", &u, &v, &w);
			u--, v--;
			G[u].push_back(v), G[v].push_back(u);
			W[u].push_back(w), W[v].push_back(w);
		}
		// Find distance in the tree from root (0)
		d[0] = 0;
		dfs(0, -1);
		// Construct the trie
		bits = find_max_bits();
		for ( int i=0; i < N; ++i ) insert( i );
		// Find the answer
		int res = 0;
		for ( int i=0; i < N; ++i ){
			res = query( d[i] );
			printf("%d\n", res ^ d[i] );
		}
	}
	return 0;
}

