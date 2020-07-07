#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN = 100005;
int A[MAXN];
int idA[MAXN];
int B[MAXN];
int idB[MAXN];
int N, Q;
int size;
long long res[MAXN];
long long FA[MAXN];
long long FB[MAXN];

struct Query {
	int l, r, k, id;
	Query(){}
	bool operator< (const Query &other) const {
		int b1 = l/size;
		int b2 = other.l/size;
		if ( b1 != b2 ) return b1 < b2;
		return r < other.r;
	}
};

Query q[MAXN];

void update( long long tree[], int p, int v ){
	for( ; p < MAXN; tree[p] += v, p += p & -p) ;
}

long long sum( long long tree[], int p ){
	long long S = 0;
	for(; p > 0 ; S += tree[p], p -= p & -p) ;
	return S;
}

void add( const int &x ){
	if ( A[x] < MAXN ) update( FA, A[x], 1 );
	if ( B[x] < MAXN ) update( FB, B[x], 1 );
}

void remove( const int &x ){
	if ( A[x] < MAXN ) update( FA, A[x], -1 );
	if ( B[x] < MAXN ) update( FB, B[x], -1 );
}

long long getAns( const int &K ){
	int sq = sqrt( K );
	int bound;
	long long fA, sA;
	long long fB, sB;
	long long res = 0;
	for ( int i=1; i <= sq; ++i ){
		bound = K / i ;
		fA = sum( FA, i ) - sum( FA, i - 1 );
		sB = sum( FB, bound ) - sum( FB, i );
		fB = sum( FB, i ) - sum( FB, i - 1 );
		sA = sum( FA, bound ) - sum( FA, i );
		res += fA * sB;
		res += fB * sA;
		res += fA*fB;
	}
	return res;
}

int main(){
	scanf("%d %d", &N, &Q);
	size = (int) sqrt(N);
	for ( int i=1; i <= N; ++i )
		scanf("%d", A + i);
	for ( int i=1; i <= N; ++i )
		scanf("%d", B + i);
	for ( int i=0; i < Q; ++i ){
		scanf("%d %d %d", &q[i].l, &q[i].r, &q[i].k);
		q[i].id = i;
	}
	sort( q, q + Q );
	// Mo Algorithm
	int l = 0;
	int r = -1;
	for ( int i=0; i < Q; ++i ){
		while ( l > q[i].l ){
			l--;
			add(l);
		}
		while ( r < q[i].r ){
			r++;
			if ( r > 0 ) add(r);
		}
		while ( l < q[i].l ){
			if ( l > 0 ) remove(l);
			l++;
		}
		while ( r > q[i].r ){
			remove(r);
			r--;
		}
		res[ q[i].id ] = getAns( q[i].k );
	}
	for ( int i=0; i < Q; ++i )
		printf("%lld\n", res[i]);
	return 0;
}
