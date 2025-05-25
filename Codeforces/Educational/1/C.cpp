#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;

#define X first
#define Y second

typedef pair<long long,long long> point;
const int MAXN = 100005;
point P[MAXN];
int ord[MAXN];

point operator+( const point &A, const point &B ){
	return point( A.X + B.X, A.Y + B.Y );
}
point operator-( const point &A, const point &B ){
	return point( A.X - B.X, A.Y - B.Y );
}
long long operator*( const point &A, const point &B ){
	// dot product
	return 1LL * A.X * B.X + 1LL * A.Y * B.Y;
}
long long operator^( const point &A, const point &B ){
	// cross product
	return 1LL * A.X * B.Y - 1LL * B.X * A.Y;
}
int sign( const point &A, const point &B, const point &C ){
	long long cr = (B - A) ^ (C - A);
	if ( !cr ) return cr;
	return ( cr < 0 )? -1:1;
}

int len( const point &A ){
	// norm of a vector
	return sqrt( A * A );
}

bool cmp( const int &i, const int &j ){
	long long cA = P[0] ^ P[i];
	long long cB = P[0] ^ P[j];
	if ( cA * cB < 0 ) return cA > cB;
	return (P[i] ^ P[j]) > 0;
}

bool less( const point &A, const point &B, const point &C, const point &D ){
	point P1( A * B, llabs(A ^ B) );
	point P2( C * D, llabs(C ^ D) );
	return (P1 ^ P2) > 0;
}

int main(){
	int N;

	scanf("%d", &N);
	for ( int i = 0; i < N; ++i ){
		scanf("%lld %lld", &P[i].X, &P[i].Y);
		ord[i] = i;
	}
	
	sort( ord + 1, ord + N, cmp );
	ord[N] = ord[0];
	P[N] = P[0];

	//for ( int i = 0; i < N; ++i )
	//	printf("(%lld, %lld)\n", P[ ord[i] ].X, P[ ord[i] ].Y);

	int idx = 0;
	for ( int i = 1; i < N; ++i ){
		if ( less( P[ ord[i] ], P[ ord[i + 1] ], P[ ord[idx] ], P[ ord[ idx + 1] ] ) )
			idx = i;
	}
	
	printf("%d %d\n", ord[idx] + 1, ord[idx + 1] + 1 );
	return 0;
}

