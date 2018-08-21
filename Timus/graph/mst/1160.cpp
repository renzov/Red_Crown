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
typedef pair<int,int> pii;
typedef pair< int , pii > edge;
const int MAXN = 1024;
const int MAXE = 15005;
int N;

int p[MAXN];
edge E[MAXE];

inline int find_set( const int &x ){
	return ( x == p[x] )? x:( p[x] = find_set( p[x] ) );
}

inline void union_set( const int &x, const int &y ){
	p[y] = x;
}

int main(){
	int M;
	int u, v, w;

	scanf("%d %d", &N, &M);
	for ( int i=1; i <= N; ++i ) p[i] = i;
	for ( int i=0; i < M; ++i ){
		scanf("%d %d %d", &u, &v, &w);
		E[i] = edge( w, pii(u, v) );
	}
	sort( E, E + M );
	int comp = N;
	for ( int i=0; i < M && comp > 1; ++i ){
		u = E[i].second.first, v = E[i].second.second;
		w = E[i].first;
		u = find_set(u), v = find_set(v);
		if ( u != v ){
			comp--;
			union_set( u, v );
		}
		if ( comp == 1 ){
			printf("%d\n", w);
			printf("%d\n", i + 1);
			for ( int j=0; j <= i; ++j )
				printf("%d %d\n", E[j].second.first, E[j].second.second);
		}
	}
	return 0;
}

