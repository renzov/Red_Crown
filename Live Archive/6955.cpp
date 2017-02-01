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
#define X first
#define Y second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int64 , int64 > point;

const int MAXN = 100005;
int N;
point P[MAXN];
int p;

long long area2( const point &a, const point &b, const point &c ){
	return (b.X - a.X)*(c.Y - a.Y) - (c.X - a.X)*(b.Y - a.Y);
}

bool check( int x, int y ){
	int cnt = 0;
	for ( int i=0; i < N; ++i ){
		if (area2(P[x], P[y], P[i]) == 0LL) cnt++;
	}
	return (cnt * 100) >= (p * N);
}

int main(){

	while ( scanf("%d %d", &N, &p) != EOF ){
		for( int i=0; i < N; ++i ){
			scanf("%lld %lld", &P[i].X, &P[i].Y);
		}
		int a, b;
		int needed = (N * p - 1) / 100;
		bool ok = (needed <= 1)? true:false;
		for ( int i=0; i < 500 && !ok; ++i ){
			a = rand() % N;
			b = rand() % N;
			if ( a != b )
				ok = check( a, b );
		}
		if (ok) puts("possible");
		else puts("impossible");
	}
	return 0;
}

