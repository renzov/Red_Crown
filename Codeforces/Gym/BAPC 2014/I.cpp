#include<cstdio>
using namespace std;

const int MAXN = 100005; 
const int LIM = 1000000000;
long long fib[50];
long long phi[50];
int K;

long long calc_phi( long long N ){
	long long res = N;
	for ( long long i=2; i*i <= N; ++i ){
		if ( N % i == 0 ) res -= res / i;
		while ( N%i == 0 ) N /= i;
	}
	if ( N > 1 ) res -= res / N;
	return res;
}

long long fast_exp( long long a, long long b, long long mod ){
	if ( b == 0 ) return 1LL;
	if ( a == 1 || b == 1 ) return a % mod;
	if ( b & 1 ) return ( a * fast_exp( a, b - 1, mod ) ) % mod;
	a = fast_exp( a , b >> 1, mod );
	return (a * a) % mod;
}

int main(){
	// preprocessing
	fib[1] = fib[2] = 1;	
	for ( K=3; (fib[K-1]+fib[K-2]) <= LIM; ++K){
		fib[K] = fib[K-1] + fib[K-2];
		phi[K] = calc_phi( fib[K] );
	}
	// Solving
	int runs, N;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &N);
		// Test soltution for every i = 1 ... K-1
		long long a, b, c;
		long long inv;
		for ( int i=K-1; i >= 2; --i ){
			if ( fib[i] <= N ){
				inv = fast_exp( fib[i-1] , phi[i] - 1, fib[i] );
				c = (N * inv) % fib[i];
				if ( c*fib[i-1] < N ){
					a = (N - c*fib[i-1]) / fib[i];
					b = a + c;
					break;
				}
			}
		}
		printf("%lld %lld\n", a, b);
	}
	return 0;
}
