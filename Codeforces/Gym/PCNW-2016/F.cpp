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

const int MAXN = 1024;

int N, L, R;

int X[MAXN];
int Y[MAXN];

vector<int> G[2*MAXN];

int comp[2*MAXN];
int dfsnum[2*MAXN];
int low[2*MAXN];
bool inS[2*MAXN] = {0};
stack<int> S;
int num = 0; 
int C = 0;

void dfs( int u ){
	low[u] = dfsnum[u] = num++;
	S.push(u);
	inS[u] = true;
	
	int v;
	for ( int i=0; i < (int) G[u].size(); ++i ){
		v = G[u][i];
		if ( dfsnum[v] == -1 ){
			dfs(v);
			low[u] = min( low[v], low[u] );
		}
		else if ( inS[v] ){
			low[u] = min( low[u], dfsnum[v] );
		}
	}
	// Check if we are in the root of the SSC
	if ( low[u] == dfsnum[u] ){
		do {
			v = S.top();
			S.pop();
			inS[v] = false;
			comp[v] = C;
		}
		while ( v != u );
		C++;
	}
}

void tarjan(){
	fill( dfsnum, dfsnum + 2*N, -1 );
	for ( int i=0; i < 2*N; ++i ){
		if ( dfsnum[i] == -1 ){
			dfs( i );
		}
	}
}

int main(){

	scanf("%d %d %d", &L, &R, &N);
	for ( int i=0; i < N; ++i )
		scanf("%d %d", X+i, Y+i);
	
	/* Create implication graph 
		Vertices from 0 ... N - 1 are postive literals
		Vertices from N ... 2N - 1 are negative literals
	*/

	for ( int i=0; i < N; ++i )
		for ( int j=i+1; j < N; ++j ){
			if ( X[i] == X[j] && abs( Y[i] - Y[j] ) < 2*R ){ // row intersection
				G[i].push_back( j + N );
				G[j].push_back( i + N );
			}
			if ( Y[i] == Y[j] && abs( X[i] - X[j] ) < 2*R ){ // column intersection 
				G[i+N].push_back(j);
				G[j+N].push_back(i);
			}
		}
	
	/* Find strongly connected components */
	tarjan();
	
	bool ok = true;
	for ( int i=0; i < N && ok; ++i )
		ok &= ( comp[i] != comp[i+N] );
	
	if (ok) puts("YES");
	else puts("NO");

	return 0;
}

