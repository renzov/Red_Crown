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

const int MAXN = 256;
int N, M;
int C[MAXN][MAXN];
// Variables for mincut
int rem[MAXN]; // remaining vertices
bool A[MAXN]; // A[i] is true iff i is in A
int W[MAXN]; // Cost of cut induced by A
int p[MAXN]; // for union find 
bool S[MAXN]; // for min cut set

inline int find_set( int x ){ return (x==p[x])? x:(p[x]=find_set(p[x])); }

int min_cut(){
	int left = N;
	int res = INT_MAX;

	for ( int i=0; i<N; ++i ) rem[i] = p[i] = i;
	
	while ( left > 1 ){ // Minimum Cut Phase
		// Initialize A and w
		A[ rem[0] ] = true;
		for ( int i=1; i < left; ++i ) {
			A[ rem[i] ] = false;
			W[ i ] = C[ rem[0] ][ rem[i] ];
		}
		int prev = rem[0]; // last vertex added to A
		int idx; // Index of the most tightly connected vertex not in A
		for ( int i=1; i < left; ++i ){ 
			idx = -1;
			for ( int j=1; j < left; ++j )
				if ( !A[ rem[j] ] && ( idx==-1 || W[j] > W[idx] ) )
					idx = j;
			// Add rem[idx] to A
			A[ rem[idx] ] = true;
			if ( i == left - 1 ){ // If its the last vertex
				if ( res > W[idx] ){ // Found a better cut 
					for ( int j=0; j < N; ++j ){
						S[j] = find_set( j ) == find_set( rem[idx] );
					}
					res = W[idx];
				}
				// merge the prev and rem[idx] vertex
				p[ rem[idx] ] = prev;
				for ( int j=0; j < left; ++j ){
					C[rem[j]][prev] = C[prev][rem[j]] += C[rem[idx]][rem[j]];
				}
				rem[idx] = rem[--left];
				break;
			}
			prev = rem[idx];
			// Update the weights of neighbors of rem[idx] not in A
			for ( int j=1; j < left; ++j ){
				if ( !A[ rem[j] ] )
					W[j] += C[ rem[idx] ][ rem[j] ];
			}
		}
	}
	return res;
}

int main(){
	int runs;
	int u, v, w;
	scanf("%d", &runs);
	for ( int k=1; k <= runs; ++k ){
		scanf("%d %d", &N, &M);
		for ( int i=0; i < N; ++i )
			fill( C[i], C[i] + N, 0 );
		for ( int i=0; i < M; ++i ){
			scanf("%d %d %d", &u, &v, &w);
			u--, v--;
			C[u][v] += w;
			C[v][u] += w;
		}
		printf("Case #%d: %d\n", k, min_cut());
		/* For debugging the min cut set
		printf("Set inducing min cut:");
		for ( int i=0; i < N; ++i ) 
			if ( S[i] ) printf(" %d", i+1);
		puts("");
		*/
	}
	return 0;
}

