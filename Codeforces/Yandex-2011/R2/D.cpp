#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN = 200005;
int size;

struct Query {
	int l, r, id;
	Query(){}
	bool operator<(const Query &other) const {
		int b1 = l / size;
		int b2 = other.l / size;
		if ( b1 != b2 ) return b1 < b2;
		return r < other.r;
	}
};

int A[MAXN];
long long res[MAXN];
Query q[MAXN];
int K[1000005] = {0};
long long sum = 0;

void add( const int &x ){
	sum -= 1LL*K[x]*K[x]*x;
	K[x]++;
	sum += 1LL*K[x]*K[x]*x;
}

void remove ( const int &x ){
	sum -= 1LL*K[x]*K[x]*x;
	K[x]--;
	sum += 1LL*K[x]*K[x]*x;
}

int main(){

	int N, Q;

	scanf("%d %d", &N, &Q);
	size = (int) sqrt( 1.0*N );
	for ( int i=0; i < N; ++i )
		scanf("%d", A + i);
	
	for ( int i=0; i < Q; ++i ){
		scanf("%d %d", &q[i].l, &q[i].r);
		q[i].l--, q[i].r--;
		q[i].id = i;
	}

	sort( q, q + Q );
	int l = 0, r = -1;
	for ( int i=0; i < Q; ++i ){
		while ( q[i].l > l ){
			remove(A[l]);
			l++;
		}
		while ( q[i].l < l ){
			l--;
			add(A[l]);
		}
		while ( q[i].r < r ){
			remove(A[r]);
			r--;
		}
		while ( q[i].r > r ){
			r++;
			add(A[r]);
		}
		res[ q[i].id ] = sum;
	}
	for ( int i=0; i < Q; ++i )
		printf("%lld\n", res[i]);
	return 0;
}
