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
int F[MAXN];
int p[MAXN];

int find_set( const int &x ){
	return ( x == p[x] )? x:( p[x] = find_set( p[x] ) );
}

void union_set( int x, int y ){
	x = find_set(x), y = find_set(y);
	if ( x != y ) p[x] = y;
}

int main(){
	int d;
	scanf("%d", &N);
	for ( int i=1; i <= N; ++i ){
		scanf("%d", F+i);
		p[i] = i;
	}
	for ( int i=1; i <= N; ++i ){
		scanf("%d", &d);
		if ( i - d >= 1 ) union_set( i , i - d );
		if ( i + d <= N ) union_set( i , i + d );
	}
	bool ok = true;
	for ( int i=1; i <= N && ok; ++i ) 
		if ( find_set(i) != find_set(F[i]) ) ok = false;
	
	if ( ok ) puts("YES");
	else puts("NO");

	return 0;
}

