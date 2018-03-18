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

const int MAXN = 1000005;
char w[MAXN];
int node;
vector<int> G[MAXN];
int d[MAXN];
map<char, int> trie[MAXN];

void insert(){
	int i, u = 0;
	int n = strlen(w);
	for ( i=0; w[i] && trie[u][ w[i] ]; ++i ){
		u = trie[u][w[i]];
	}	
	if ( w[i] ){ 
		int prev = u;
		int last_u = u;
		int last_i = i;
		for ( ; w[i] ; ++i ){
			u = trie[prev][ w[i] ] = ++node;
			G[u].push_back(prev), G[prev].push_back(u);
			prev = u;
		}
		int last = prev;
		for ( i = last_i; i < n - 2; ++i ){
			u = trie[last_u][ w[i] ];
			G[u].push_back(last);
			last_u = u;
		}
	}
	
}

int main(){
	int N, M;
	scanf("%d %d", &N, &M);
	node = 0;
	for ( int i=0; i < N; ++i ){
		scanf("%s", w);
		insert();
	}
	fill( d, d + node + 1, -1 );
	d[0] = 0;
	queue<int> q;
	q.push(0);
	int u, v;
	while ( !q.empty() ){
		u = q.front();
		q.pop();
		for ( int i=0; i < (int)G[u].size(); ++i ){
			v = G[u][i];
			if ( d[v] == -1 ){
				d[v] = d[u] + 1;
				q.push(v);
			}
		}
	}
	int j;
	for ( int i=0; i < M; ++i ){
		scanf("%s", w);
		u = 0;
		for ( j = 0; w[j] && trie[ u ][ w[j] ] ; ++j ){
			u = trie[u][ w[j] ];
		}
		printf("%d\n", d[ u ] + ( strlen(w) - j ));
	}


	return 0;
}

