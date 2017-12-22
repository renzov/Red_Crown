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
typedef pair< int, pii > edge;

const int MAXN = 500;

int N, M, K;
int C[MAXN];
int p[MAXN];
int ncomp;
edge E[200*200];

inline void make_set( int x ){ p[x] = x; }
inline int find_set( int x ){ return ( x==p[x] )? x:( p[x] = find_set( p[x] ) ); }
void join_set( int x, int y ){
	x = find_set(x);
	y = find_set(y);
	if ( x != y ){
		p[y] = x, ncomp--;
	}
}

int main(){

	int runs;
	int cases = 0;
	int u, v, w;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d %d", &N, &M, &K);
		
		for ( int i=1; i <= N; ++i ) make_set(i);
		
		ncomp = N;

		for ( int i=0; i < K; ++i ){
			scanf("%d", C+i);
			if ( i > 0 ){ 
				join_set( C[i-1], C[i] );
			}
		}
		for ( int i=0; i < M; ++i ){
			scanf("%d %d %d", &u, &v, &w);
			E[i].first = w, E[i].second.first = u, E[i].second.second = v;
		}
		sort( E, E + M );
		int res = 0;
		for ( int i=0; i < M && ncomp > 1; ++i ){
			u = E[i].second.first;
			v = E[i].second.second;
			u = find_set(u);
			v = find_set(v);
			if ( u != v ){ 
				join_set(u, v), res += E[i].first;
			}
		}
		cases++;
		printf("Case #%d: %d\n", cases, res);
	}
	return 0;
}

