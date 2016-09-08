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
#define X first
#define Y second 
using namespace std;

typedef pair< int , int > point;
const int MAXN = 2005;
point P[MAXN];
point O;
int kind[MAXN];


int area2( const point &a, const point &b, const point &c ){
	int r = (b.X-a.X)*(c.Y-a.Y) - (c.X - a.X)*(b.Y - a.Y);
	if ( r > 0 ) return 1;
	if ( r < 0 ) return -1;
	return 0;
}

bool cmp( const point &p, const point &q ){
	int a = area2( O, p, q );
	if ( a > 0 ) return true;
	if ( a < 0 ) return false;
	if ( p.X < q.X || (p.X == q.X && p.Y < q.Y) ) return true;
	return false;
}

int main(){
	int runs;
	int N;
	scanf("%d", &runs);
	while (runs--){
		scanf("%d", &N);
		map<point, int> idx;
		for ( int i=0; i < N; ++i ){ 
			scanf("%d %d", &P[i].X, &P[i].Y);
			idx[ P[i] ] = i;
		}
		int imin = min_element( P, P + N ) - P;
		if ( imin ) swap( P[0], P[imin] );
		O = P[0];
		sort( P + 1, P + N, cmp );
		
		int type = 1;
		kind[1] = type;
		for ( int i=2; i < N; ++i ){
			if ( area2(O, P[i-1], P[i]) == 0 ) kind[i] = kind[i-1];
			else kind[i] = ++type;
		}
		printf("%d", idx[ O ]);
		int i;
		for ( i=1; kind[i] != kind[N-1]; ++i )
			printf(" %d", idx[P[i]]);
		for ( int j=N-1; j >= i; --j )
			printf(" %d", idx[P[j]]);
		puts("");
	}
	return 0;
}

