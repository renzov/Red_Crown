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
typedef pair< int , int > point;

const int MAXN = 500000;
int segL[4*MAXN + 10];
int segR[4*MAXN];
int cnt[MAXN + 5] = {0};
int ord[MAXN + 5];
point P[MAXN + 5];
point Q[MAXN + 5];
int res[MAXN + 5];
int N, M;

bool cmp( const int &i, const int &j ){
	return Q[i] < Q[j];
}

void build( int node, int L, int R ){
	if ( L==R ){
		segL[node] = 0;
		segR[node] = cnt[L];
		return;
	}
	int M = ( L + R ) >> 1;
	build( node << 1, L, M );
	build( (node << 1) | 1, M + 1, R );

	segL[node] = segL[node<<1] + segL[(node<<1)|1];
	segR[node] = segR[node<<1] + segR[(node<<1)|1];
}

void update( int node, int L, int R, int p ){
	if ( L == R ){
		segL[node]++;
		segR[node]--;
		return;
	}
	int M = ( L + R ) >> 1;
	
	if ( p <= M ) update(node<<1, L, M, p);
	else update((node<<1)|1, M+1, R, p);

	segL[node] = segL[node<<1] + segL[(node<<1)|1];
	segR[node] = segR[node<<1] + segR[(node<<1)|1];
}

point query(int node, int L, int R, int l, int r ){
	if ( l==L && r==R ){
		return point( segL[node], segR[node] );
	}
	int M = ( L + R ) >> 1;
	if ( r <= M ) return query( node << 1, L, M, l , r );
	else if ( l > M ) return query( (node<<1)|1, M + 1, R, l, r );

	point A, B;
	A = query( node<<1, L, M, l, M );
	B = query( (node<<1)|1, M+1, R, M+1, r );
	return point( A.X + B.X, A.Y + B.Y );
}

int main(){
	int runs;

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d", &N, &M);
			
		for ( int i=0; i < N; ++i ){
			scanf("%d %d", &P[i].X, &P[i].Y);
			cnt[ P[i].Y ]++;
		}
		sort( P , P + N );

		for ( int i=0; i < M; ++i ){
			scanf("%d %d", &Q[i].X, &Q[i].Y);
			ord[i] = i;
		}
		sort( ord, ord + M, cmp );
		
		build( 1, 0, MAXN );

		int j = 0;
		int idx;
		int x;
		int A, B, C, D;
		pair<int,int> tmp;

		for ( int i=0; i < M; ++i ){

			idx = ord[i];
			x = Q[idx].X;
			
			//printf("%d query: x = %d y = %d\n", i, x, Q[idx].Y);

			while ( j < N && P[j].X < x ){ // update
				update( 1, 0, MAXN, P[j].Y );
				//printf("Advance %d\n", j);			
				j++;
			}

			tmp = query( 1, 0, MAXN, Q[idx].Y,  MAXN );
			B = tmp.X;
			C = j - B;
			A = tmp.Y;
			D = N - j - A;
			//printf("A = %d\tB = %d\tC = %d\tD = %d\n", A, B, C, D);
			res[ idx ] = abs( A + C - B - D );
		}

		for ( int i=0; i < M; ++i ) printf("%d\n", res[i]);

		if ( runs ){ 
			puts("");
			fill( cnt, cnt + MAXN + 1, 0 );
		}
	}
	return 0;
}

