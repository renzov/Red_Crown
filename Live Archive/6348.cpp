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

const int MAXN = 100005;
int N;
int X1[MAXN];
int X2[MAXN];
int Y1[MAXN];
int Y2[MAXN];
int res[MAXN];

set< pii > U;
set< pii > L;

struct event {
	int x, idx;
	bool in;
	
	event(){}
	event( int p, int id, bool t ){ x = p, idx = id, in = t; }
	
	bool operator<( const event &that ) const {
		if ( x != that.x ) return x < that.x;
		return in < that.in;
	}
};

event E[2*MAXN];

int get( const int &y1, const int &y2 ){
	if ( L.empty() ) return -1;
	set<pii>::iterator it = L.lower_bound( pii( y1 , -1 ) );
	if ( it == L.begin() ) return -1;
	it--;
	int idx = it->second;
	if ( Y1[idx] < y1 && y2 < Y2[idx] ) return idx;
	it = U.lower_bound( pii( y1 , -1 ) );
	if ( it == U.begin() ) return -1;
	it--;
	return res[it->second];
}


int main(){
	scanf("%d", &N);
	
	for ( int i=0; i < N; ++i ){
		scanf("%d %d %d %d", X1+i, Y1+i, X2+i, Y2+i);
		E[2*i] = event( X1[i], i, true );
		E[2*i + 1] = event( X2[i], i , false );
	}
	sort( E, E + 2*N );
	int idx;
	for ( int i=0; i < 2*N; ++i ){
		idx = E[i].idx;
		if ( E[i].in ){
			res[ idx ] = get( Y1[idx], Y2[idx] );

			L.insert( pii( Y1[idx], idx ) );
			U.insert( pii( Y2[idx], idx ) );
		}
		else {
			L.erase( pii( Y1[ idx ] , idx ) );
			U.erase( pii( Y2[ idx ] , idx ) );	
		}
	}
	for (int i=0; i < N; ++i) printf("%d\n", res[i]);
	return 0;
}

