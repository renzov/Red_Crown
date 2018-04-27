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

int deg[MAXN];
int p[MAXN];
int sum[MAXN];

inline int find_set( const int &x ){
	return x == p[x]? x: ( p[x] = find_set( p[x] ) );
}

inline void union_set( const int &x, const int &y ){
	if ( x != y ) p[y] = x; 
}

int main(){
	int u, v;
	for ( int i=1; i <= 1000; ++i ) p[i] = i;
	while ( scanf("%d %d", &u, &v) == 2 ){
		union_set( find_set(u), find_set(v) );
		deg[u]++, deg[v]++;
	}
	for ( int i=1; i <= 1000; ++i ) sum[ find_set(i) ] += deg[i];
	bool ok = true;
	for ( int i=1; i <= 1000 && ok; ++i ) ok &= ((sum[i] % 4) == 0);
	puts( ok? "1":"0" );
	return 0;
}

