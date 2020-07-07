#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;
const int MAXN = 200005;

int A[MAXN];
long long V[MAXN];
int C[MAXN];
long long costR[MAXN];
long long costL[MAXN];

int main(){
	int N, K;

	scanf("%d %d", &N, &K);
	for ( int i=0; i < N; ++i )
		scanf("%d", A + i );

	sort( A, A + N );
	int M = 0;
	int last = A[0], cnt = 0;
	for ( int i=0; i < N; ){
		while ( i < N && A[i] == last ) cnt++, i++;
		C[M] = cnt;
		V[M++] = last;
		if ( i < N ) last = A[i], cnt = 0;
	}

	costR[M - 1] = 0;
	int sum = 0;
	for ( int i=M - 2; i >= 0; --i ){
		sum += C[ i + 1 ];
		costR[ i ] = costR[ i + 1 ] + sum * ( V[i + 1] - V[i] );
	}

	costL[0] = 0;
	sum = 0;
	for ( int i=1; i < M; ++i ){
		sum += C[ i - 1 ];
		costL[i] = costL[ i - 1 ] + sum * ( V[i] - V[i - 1] );
	}

	long long res = LLONG_MAX;
	long long tmp;
	int sumLeft = 0;
	int sumRight = N - C[0];
	int l, r;
	for ( int i=0; i < M; ++i ){
		if ( C[i] >= K ){ 
			res = 0;
		}
		else {
			if ( (sumLeft + C[i]) >= K ){
				res = min( res, costL[i - 1] + sumLeft * (V[i] - V[i - 1] - 1) + ( K - C[i] ) );
			}
			if ( (sumRight + C[i]) >= K ){
				res = min( res, costR[i + 1] + sumRight * (V[i + 1] - V[i] - 1) + ( K - C[i] ) );
			}
			// We take from both sides
			if ( i > 0 && ((i + 1) < M) ){
				tmp = costL[i - 1] + sumLeft * (V[i] - V[i - 1] - 1) +  costR[i + 1] + sumRight * (V[i + 1] - V[i] - 1); 
				res = min( res, tmp + ( K - C[i] ) );
			}
		}
		sumLeft += C[i];
		if ( i + 1 < M ) sumRight -= C[i + 1];
	}
	printf("%lld\n", res);

	return 0;
}
