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
const int MAXM = 1000010;
int N;
int M; // Number of nodes in the trie
int sum;

map<char,int> T[MAXM];
bool endword[MAXM] = {0};
int f[MAXM];

void insert(char *s){
	int u = 0; // Root
	int v;
	for ( int i=0; s[i]; ++i ){
		v = T[u][ s[i] ];
		if ( v == 0 ){
			v = T[ u ][ s[i] ] = M++;
		}
		u = v;
	}
	endword[u] = true;
}

void dfs( int u, int p ){
	if ( u == 0 ) f[u] = 0;
	else if ( endword[u] || T[u].size() > 1 ) f[u] = 1;
	else f[u] = 0;
	
	if ( p != -1 ) f[u] += f[p];
	if ( endword[u] ) sum += f[u];
	
	for ( map<char,int>::iterator it = T[u].begin(); it != T[u].end(); ++it  ){
		dfs( it->second, u );
	}
	// Clear memory for next testcase 
	T[u].clear();
	endword[u] = false;
}

int main(){
	char s[128];
	while ( scanf("%d", &N) != EOF ){
		M = 1;
		for ( int i=0; i < N; ++i ){
			scanf("%s", s);
			insert( s );
		}
		sum = 0;
		dfs( 0 , -1 );
		printf("%0.2f\n", 1.0*sum / N );
	}
	return 0;
}

