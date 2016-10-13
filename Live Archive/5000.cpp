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

const int MAXN = 10005;

int K, N, S, D;
int X[MAXN];
int Y[MAXN];

pii I[MAXN];

int root( const long long &val ){
	long long r = (long long)sqrt( (double)val ) + 1;
	while ( r*r > val ) r--;
	return (int) r;
}

bool test( int w ){
	int M;
	int t;
	for ( int i=0; i<N; ++i ){
		M = Y[i] - K + w;
		t = root( (long long)D*D - (long long)M*M ); 
		I[i] = pii( X[i] + t , X[i] - t );
	}
	sort( I , I + N );
	int res = 0;
	int last = -INT_MAX;
	for ( int i=0;  i < N; ++i ){
		if ( last < I[i].second ){
			last = I[i].first;
			res++;
		}
	}
	return res <= S;
}

int main(){
	int ymax;
	int runs;
	int l, r, m;

	scanf("%d", &runs);
	for ( int cases = 1; cases <= runs; ++cases ){
		scanf("%d %d %d %d", &K, &N, &S, &D);
		ymax = -INT_MAX;
		for ( int i=0; i < N; ++i ){
			scanf("%d %d", X+i, Y+i);
			if ( Y[i] > ymax ) ymax = Y[i];
		}
		r = D - ymax + K + 1;
		if ( r <= 1 || !test(1) ){
			printf("Case %d: IMPOSSIBLE\n", cases);
			continue;
		}
		l = 1;
		while ( r - l > 1 ){
			m = ( l + r ) / 2;
			if ( test(m) )
				l = m;
			else 
				r = m;
		}
		printf("Case %d: %d\n", cases, l);
	}
	return 0;
}

