#include <cstdio>
#include <set>
#include <cstdlib>
#include <algorithm>

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
typedef pair< int , int > point;

int N, K;
const int M = 368;
const int MAXS = 100 * 740 * 740;
point P[MAXS + 5];

int main(){
	int x, y, b;
	int lx, ly, rx, ry;
	long long A, C;
	int S = 0;

	scanf("%d %d", &N, &K);
	for ( int i=0; i < K; ++i ){
		scanf("%d %d %d", &x, &y, &b);
		lx = max(x - M, 0);
		rx = min(x + M, N);
		ly = max(y - M, 0);
		ry = min(y + M, N);
		for ( int a = lx; a <= rx; ++a )
			for ( int c = ly; c <= ry; ++c ){
				A = abs( x - a );
				C = abs( y - c );
				if ( A*A*A + C*C*C <= b ){
					P[S++] = point(a,c);
				}
			}
	}
	sort( P, P + S );
	S = unique(P , P + S) - P;
	printf("%lld\n", (long long)(N+1)*(N+1) - S);
	return 0;
}

