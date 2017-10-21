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

struct node {
	map<char, int> link;
	node(){};
};

node pref[100005];
node suff[100005];
long long start[50];

void insert( node* trie, char *s, int &size ){
	int idx = 0; // begin at root 
	int nxt;
	for ( int i=0; s[i]; ++i ){
		nxt = trie[idx].link[ s[i] ];
		if ( nxt == 0 ){ 
			trie[size].link.clear(); // Clear node information 
			nxt = trie[idx].link[ s[i] ] = size++;
		}
		idx = nxt;
	}
}

int N; // Number of prefix nodes
int M; // Number of suffix nodes 
int S, P;
char str[1024];

void dfs_suffix( int u, int d ){
	for ( map<char,int>::iterator it = suff[u].link.begin(); it != suff[u].link.end(); ++it ){
		if ( d > 0 ) start[ it->first - 'a' ]++;
		dfs_suffix( it->second, d + 1 );
	}
}

long long dfs_pref( int u, int d ){
	long long res = 0;
	if ( d > 0 ) res += (M - 1); // Number of nodes - root in suffix trie
	for ( map<char,int>::iterator it = pref[u].link.begin(); it != pref[u].link.end(); ++it ){
		if ( d > 0 ) res -= start[ it->first - 'a' ]; // substract over counting 
		res += dfs_pref( it->second, d + 1 );
	}
	return res;
}

int main(){
	while ( scanf("%d %d", &P, &S) && S ){
		// Init preffix trie
		N = 1;
		pref[0].link.clear();
		for ( int i=0; i < P; ++i ){
			scanf("%s", str);
			insert ( pref , str , N );
		}
		// Init suffix trie
		M = 1;
		suff[0].link.clear();
		for ( int i=0; i < S; ++i ){
			scanf("%s", str);
			reverse( str, str + strlen(str) );
			insert( suff, str, M );
		}
		// Calculate subtree size suffix trie
		fill( start, start + 30, 0 );
		dfs_suffix( 0 , 0 );
		printf("%lld\n", dfs_pref( 0, 0 ));
	}
	return 0;
}

