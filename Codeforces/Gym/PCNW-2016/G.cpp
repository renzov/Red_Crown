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

char H[64][64];
bool vis[64][64] = {0};
int N, M;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int idx[64][64];
int V = 0;
int A = 0; 
int vertex[2048]; // max vert. = 40*40 < 2048
int match[2048]; // V \ A
bool seen[2048];
vector<int> G[2048];


void flood( const int &x, const int &y ){
	int nx, ny;

	vis[x][y] = true;
	for( int i=0; i < 4; ++i ){
		nx = x + dx[i];
		ny = y + dy[i];
		if ( nx < 0 || ny < 0 || nx >= N || ny >= M ) continue;
		if ( H[nx][ny] == 'C' ) H[nx][ny] = 'W'; // Convert adjacent clouds in water
		else if ( H[nx][ny] == 'L' && !vis[nx][ny] ){
			flood( nx, ny );
		}
	}
}

bool alt_path( int u ){
	int v;
	if ( seen[u] ) return false;
	seen[u] = true;
	for ( int i=0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( match[v] == -1 || alt_path( match[v] ) ){
			match[v] = u;
			return true;
		}
	}
	return false;
}

int main(){
	int res = 0;

	scanf("%d %d", &N, &M);
	for ( int i=0; i < N; ++i ){
		scanf("%s", H[i]);		
		fill( vis[i], vis[i] + M, false );
		fill( idx[i], idx[i] + M, -1 );		
	}
	// Counting number of components
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < M; ++j ){
			if ( H[i][j] == 'L' && !vis[i][j] ){
				flood( i , j );
				res++;
			}
		}

	// Number bipartite graph of cloud vertices
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < M; ++j ){
			if ( H[i][j] == 'C' ){
				idx[i][j] = V;
				if ( (i + j) & 1 ){
					vertex[A++] = V;
				}
				V++;
			}
		}

	int nx, ny;
	int u;

	for ( int i=0; i < N; ++i )
		for ( int j=0; j < M; ++j ){	
			if ( idx[i][j] != -1 && ( (i + j) & 1 ) ){
				u = idx[i][j];
				for ( int k=0; k < 4; ++k ){
					nx = i + dx[k];
					ny = j + dy[k];
					if ( nx >= 0 && ny >= 0 && nx < N && ny < M && idx[nx][ny] != -1 ){
						G[ u ].push_back( idx[nx][ny] );
					}
				}
			}
		}

	// find max. bipartite matching.
	int matching = 0;
	fill( match, match + V, -1 );	
	for ( int i=0; i < A; ++i ){

		for ( int j=0; j < A; ++j ) seen[ vertex[j] ] = false; 
	
		if ( alt_path( vertex[i] ) ){
			matching++;
		}
	}

	printf("%d\n", res + (V - matching) );
	return 0;
}

