#include<cstdio>
#include<algorithm>
using namespace std;
const long long MOD = 1000000007LL;
const int MAXN = 100000;
int A[MAXN + 5];
int W[MAXN + 5];
long long fact[MAXN + 5];

void preprocess(){
	fact[0] = 1LL;
	for ( int i=1; i <= MAXN; ++i ){
		fact[i] = ( i * fact[i - 1] ) % MOD;
	}
}

void process(){
	int N;

	scanf("%d", &N);
	for ( int i=0; i < N; ++i )
		scanf("%d", A + i);
	sort( A, A + N );
	for ( int i=0; i < N; ){
		int j = i;
		while ( j + 1 < N && A[i] == A[j + 1] )
			j++;
		int K = j - i + 1;
		for ( int p = 1; p <= K; ++p ){
			W[i + p - 1] = 2*p - K - 1;
		}
		i = j + 1;
	}
	
	sort( W, W + N );
	long long res = 1LL;
	for ( int i=0; i < N; ){
		int j = i;
		while ( j + 1 < N && W[i] == W[j + 1] )
			j++;
		int K = j - i + 1;
		i = j + 1;
		res *= fact[ K ];
		res %= MOD;
	}
	printf("%lld\n", res);
}

int main(){
	int runs;
	preprocess();
	scanf("%d", &runs);
	while ( runs-- ) process();
	return 0;
}
