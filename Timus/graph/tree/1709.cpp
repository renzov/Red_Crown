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
const int MAXN = 128;
int N;

int M[MAXN][MAXN];
int R[MAXN][MAXN] = {0};
int dfsnum[MAXN];
int V[MAXN];
int m = 0;
int del = 0;
void dfs( int u, int p ){
	dfsnum[u] = m++;
	for ( int v = 0; v < N; ++v ){
		if ( v != p && v != u && M[u][v] ){
			if ( dfsnum[v] == -1 ) {
				dfs( v, u );
			}
			else {
				R[u][v] = -1;
				del++;
			}
		}
	}
}


int main(){
	int D, A;
	int n = 0;
	int u, v;
	char s[MAXN];

	scanf("%d %d %d", &N, &D, &A);
	for (int i=0; i < N; ++i){
		scanf("%s", s);
		for ( int j=0; j < N; ++j ){
			M[i][j] = s[j] - '0';
		}
	}
	fill( dfsnum, dfsnum + N, -1 );
	for ( int i=0; i < N; ++i ){
		if ( dfsnum[i] == -1 ){
			dfs( i , -1 );
			V[n++] = i;
		}
	}
	for ( int i=1; i < n; ++i ){
		u = V[i-1]; 
		v = V[i];
		R[u][v] = R[v][u] = 1; 
	}
	// Printing answer
	del >>= 1;
	printf("%lld\n", (long long)del*D + (long long)(n - 1)*A);
	for ( int i=0; i < N; ++i ){
		for ( int j=0; j < N; ++j ){
			if ( R[i][j] == 0 ) putchar('0');
			else if ( R[i][j] == 1 ) putchar('a');
			else if ( R[i][j] == -1 ) putchar('d');
		}
		puts("");
	}
	return 0;
}

