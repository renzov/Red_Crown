#include<cstdio>
#include<algorithm>
using namespace std;
const int NLOG = 17;
const int MOD = (1 << 16) - 1;
const int MAXN = 100005;

int N;
int A[NLOG][MAXN];
int bits[NLOG];

int main(){
	int mask;
	int eps;
	int x;
	int cases = 0;
	long long res;
	int *a;
	int l, r;
	int L, R;
	int m;

	for ( int i=1; i <= 16; ++i )
		bits[i] = ( 1 << i ) - 1;

	while ( scanf("%d" , &N) && N != -1 ){
		for ( int i=0; i < N; ++i ){
			scanf("%d", &x);
			for ( int j=1; j < NLOG; ++j )
				A[j][i] = x & bits[j];
		}
		for ( int i=1; i < NLOG; ++i )
			sort( A[i], A[i] + N );
		
		eps = 0;
		res = 0;
		char op[2];
		while ( scanf("%s", op) == 1 && op[0] != 'E' ){
			scanf("%d", &x);
			if ( op[0] == 'C' ){
				eps += x;
				eps &= MOD;
			}
			else {
				a = A[x + 1];
				m = eps & bits[x];
				if ( (eps >> x)&1 ){	// eps % 2^x >= 2^(x-1)
					r = (1 << x) - m - 1;
					res += ( upper_bound( a, a + N, r ) - a );
					L = lower_bound( a, a + N, (1 << (x + 1) ) - m ) - a;
					res += ( N - L );
				}
				else {
					r = ( 1 << (x + 1) ) - m - 1;
					l = ( 1 << x ) - m;
					R = upper_bound( a, a + N, r ) - a;
					L = lower_bound( a, a + N, l ) - a;
					res += ( R - L );
				}
			}
		}
		printf("Case %d: %lld\n", ++cases, res);
	}
	return 0;
}
