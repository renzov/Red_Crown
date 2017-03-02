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

const int MAXN = 505;
int N, M;

vector<int> D[ MAXN ];
map<string,int> idx;
char term[MAXN][10];
int word[ MAXN ];

int cntName, cntWord;

char name[20];
char c;
char S[2005];
int memo[MAXN][2005] = {0};
int ts[MAXN][2005];
int t;

int getid(){
	if ( idx.count(name) ) return idx[name];
	return idx[name] = cntName++;
}

void read_eq(){
	scanf("%s %c", name, &c);
	int u = getid();
	int v, w;
	scanf("%s", name);
	if ( !islower(name[0]) ){
		v = getid();
		scanf(" %c %s", &c, name);
		w = getid();
		D[u].push_back( v );
		D[u].push_back( w );
	}
	else {
		strcpy(term[cntWord], name);
		word[ u ] = cntWord++;		
	}
}

int dfs( int u, int p ){
	if ( ts[u][p] >= t ) return memo[u][p];
	
	ts[u][p] = t;
	memo[u][p] = p;
	int &ref = memo[u][p];
	
	if ( word[u] != -1 ){
		char *s = term[ word[u] ];
		for ( int i=0; ref < M && s[i]; ++i ){
			if ( S[ref] == s[i] ) ref++;
		}
		return ref;
	}
	else {
		return ref = dfs( D[u][1] , dfs( D[u][0], p ) );	
	}
}

int main(){
	int runs;
	t = 0;
	scanf("%d", &runs);
	while ( runs-- ){
		t++;
		scanf("%d", &N);
		fill( word, word + N, -1 );
		cntWord = cntName = 0;
		for ( int i=0; i < N; ++i ) read_eq();

		scanf("%s", name);
		int root = getid();
		scanf("%s", S);
		M = strlen(S);
		
		if ( dfs( root, 0 ) >= M ) puts("YES");
		else puts("NO");

		if ( runs ){
			idx.clear();
			for ( int i=0; i<N; ++i ) D[i].clear();
		}
	}
	return 0;
}

