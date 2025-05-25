#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;

vector<long long> primes;
bool nprime[100005];

void sieve(){
	primes.push_back( 2 );
	for ( long long i = 3; i < 100000; i += 2 ){
		if ( !nprime[i] ){
			primes.push_back( i );
			for ( int j = 3 * i; j < 100000; j += (i << 1) )
				nprime[i] = true;
		} 
	}
}

long long fast_pow( const long long &A, const long long &B, const long long MOD ){
	if ( B == 0 ) return 1LL;
	if ( B == 1 ) return A % MOD;
	if ( B & 1 ) return ( A * fast_pow( A, B - 1, MOD ) ) % MOD;
	long long C = fast_pow( A, B >> 1, MOD );
	return ( C * C ) % MOD;
}

vector<long long> factorize( long long n ){
	vector<long long> ans;
	for ( int i = 0; i < (int)primes.size() && n > 1; ++i ){
		if ( (n % primes[i]) == 0 ){
			ans.push_back( primes[i] );
			while ( ( n % primes[i] ) == 0 )
				n /= primes[i];
		}
	}
	if ( n > 1 ) ans.push_back( n );
	return ans;
}

void process( const long long &N, const long long &E, const long long &C ){
	// First we factorize N
	vector<long long> facN = factorize( N );
	assert( facN.size() == 2 );
	// phi(N)
	long long phi = (facN[0] - 1) * (facN[1] - 1);
	// Calculate the inverse E mod phi(N) 
	vector<long long> facP = factorize( phi );
	long long phi2 = phi;
	for ( int i = 0; i < (int)facP.size(); ++i ){
		phi2 /= facP[i];
		phi2 *= (facP[i] - 1);
	}
	long long D = fast_pow( E, phi2 - 1, phi );
	// Find M
	long long M = fast_pow( C, D, N );
	printf("%lld\n", M );
}

int main(){
	long long N, E, C;
	sieve();
	while ( scanf("%lld %lld %lld", &N, &E, &C ) ==  3 )
		process( N, E, C );
	return 0;
}
