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

int N, F, M;
const int MAXN = 305;

int G[MAXN][MAXN];
map<int,int> H[MAXN];

void getops( int b, int f, int *vert, int *w, int &size ){
	size = 0;
	map<int,int>::iterator it = H[b].lower_bound( f );
	if ( it != H[b].end() ){
		vert[size] = it->second, w[size] = it->first - f;
		size++;
	}
	if ( it == H[b].end() || f < it->first ){ // important: f > 0 (0 is always in the map)
		it--;
		vert[size] = it->second, w[size] = f - it->first;
		size++;
	}
}

int main(){
	int runs;
	int b1, f1, b2, f2;
	int u, v, t;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d %d", &N, &F, &M);
		// init the dist matrix
		for ( int i=0; i < (N + 2*M); ++i ){
			G[i][i] = 0;
			for ( int j=0; j < (N + 2*M); ++j )
				G[i][j] = G[j][i] = INT_MAX; 
		}
		for ( int i=0; i < N; ++i ) H[i].clear(); 
		int n = 0;
		for ( int i=0; i < N; ++i )
			H[ i ][ 0 ] = n++;

		for ( int i=0; i < M; ++i ){
			scanf("%d %d %d %d %d", &b1, &f1, &b2, &f2, &t);
			b1--, b2--, f1--, f2--;
			if ( H[b1].find(f1) == H[b1].end() ) H[b1][f1] = n++;
			u = H[b1][f1];
			if ( H[b2].find(f2) == H[b2].end() ) H[b2][f2] = n++;
			v = H[b2][f2];
			G[u][v] = G[v][u] = t;
		}
		// Setting the in building distances and adjacent building distance 
		map<int,int>::iterator it, it2;
		for ( int i=0; i < N; ++i ){
			it2 = H[i].begin();
			it = it2++;
			for ( ; it2 != H[i].end() ; it=it2++ ){
				u = it->second, v = it2->second;
				G[u][v] = G[v][u] = it2->first - it->first;
			}
			u = H[i].begin()->second;
			v = H[ (i+1)%N ].begin()->second;
			G[u][v] = G[v][u] = 1;
		}
		// Floyd Warshall
		for ( int k=0; k < n; ++k )
			for ( int i=0; i < n; ++i )
				for ( int j=0; j < n; ++j ){
					if ( G[i][k] < INT_MAX && G[k][j] < INT_MAX )
						G[i][j] = min( G[i][j] , G[i][k] + G[k][j] ); 
				}
		// Queries
		int Q;
		int v1[2], v2[2];
		int w1[2], w2[2];
		int s1, s2;
		int res;
		scanf("%d", &Q);
		while ( Q-- ){
			scanf("%d %d %d %d", &b1, &f1, &b2, &f2 );
			b1--, f1--, b2--, f2--;
			getops( b1, f1, v1, w1, s1 );
			getops( b2, f2, v2, w2, s2 );
			// Distance without bridges
			if ( b1 != b2 ){
				res = f1 + f2;
				if ( b1 < b2 ) res += min( b2 - b1, N - b2 + b1 );
				else res += min( b1 - b2, N - b2 + b1 );
			}
			else {
				res = abs( f1 - f2 );
			}
			for ( int i=0; i < s1; ++i )
				for ( int j=0; j < s2; ++j ){
					u = v1[i], v = v2[j];
					res = min( res, G[u][v] + w1[i] + w2[j] );
				}
			printf("%d\n",res);
		}
	}
	return 0;
}

