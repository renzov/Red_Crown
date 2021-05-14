#include<cstdio>
#include<cmath>
#include<cassert>
using namespace std;

int primes[16];
int K;

void decompose( int N ){
	K = 0;
	// find the prime factors of N
	if ( !(N & 1) ){ 
		primes[K++] = 2;
		while ( !(N & 1) ) N >>= 1;
	}

	for ( int i=3; i*i <= N; i += 2 )
		if ( (N % i) == 0 ){
			primes[K++] = i;
			while ( (N % i) == 0 ) N /= i;
		}
	if ( N > 1 ) primes[K++] = N;
}

long long f( const long long &X ){
	if ( X == 0 ) return 0;
	long long p;
	long long res = X;
	int cnt;

	for ( int i = 1; i < (1 << K); ++i ){
		p = 1;
		cnt = 0;
		for ( int j=0; j < K; ++j )
			if ( (i >> j) & 1 ){
				p *= primes[j];
				cnt ^= 1;
			}

		if ( cnt ){	// Intersection of odd number of sets
			res -= X/p;
		}
		else {	// Intersection of even number of sets
			res += X/p;
		}
	}
	return res;
}

void process(){
	int N;
	long long A, B;
	scanf("%lld %lld %d", &A, &B, &N);
	decompose( N );
	printf("%lld\n", f(B) - f(A - 1) );
}

int main(){
	int T;
	scanf("%d", &T);
	for ( int i=1; i <= T; ++i ){
		printf("Case #%d: ", i);
		process();
	}
	return 0;
}
