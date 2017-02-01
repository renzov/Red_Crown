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

const int MAXN = 1000;

bool type[MAXN];
int prefD[MAXN];
int detD[MAXN];
int prefC[MAXN];
int detC[MAXN];
int C,D;

bool G[MAXN][MAXN];

bool vis[MAXN];
int match[MAXN];

void init(){
	for ( int i=0; i < D ; ++i )
		for ( int j=0; j < C ; ++j )
			if ( detD[i] == prefC[j] || detC[j] == prefD[i] )
				G[i][j] = true;
			else 
				G[i][j] = false;
}

bool alt_path( int u ){
	if ( vis[u] ) return false;
	vis[u] = true;
	for ( int w=0; w < C; ++w ){
		if ( G[u][w] ){ 
			if ( match[w] == -1 || alt_path(match[w]) ){
				match[w] = u;
				return true;
			}
		}
	}
	return false;
}

int bpm(){
	int res = 0;
	fill( match, match + C, -1 );
	for (int i=0; i < D; i++){
		fill( vis , vis + D , false );
		if ( alt_path(i) ) res++;
	}
	return res;
}

int main(){
	int t,p,c,d,v;
	int runs;

	scanf("%d",&runs);

	while ( runs-- ){
		scanf("%d %d %d",&c,&d,&v);
		C = D = 0;
		for ( int i=0; i < v; ++i ){
			scanf(" %c%d",&t,&p);
			if (t=='D'){
				prefD[D] = p;
				scanf(" %c%d",&t,&p);
				detD[D] = p;
				D++;
			}
			else {
				prefC[C] = p;
				scanf(" %c%d", &t,&p);
				detC[C] = p;
				C++;
			}
		}
		init();
		//printf("%d\n", v - bpm() );
		cout << v - bpm() << endl;
	}
	return 0;
}

