#include<cstdio>
using namespace std;
const int MAXN = 1000005;
const long long UB = 25505460948LL;
long long prime[MAXN];
int P;
bool composite[MAXN] = {0};
int mu[MAXN];

void sieve(const int &n){
	mu[1] = 1;
	for ( int i=2; i < n; ++i ){
		if ( !composite[i] ) prime[P++] = i, mu[i] = -1;
		for ( int j=0; j < P && i * prime[j] < n; ++j ){
			composite[i * prime[j]] = true;
			if ( i % prime[j] == 0 ){
				mu[ i * prime[j] ] = 0;
			}
			else {
				mu[ i * prime[j] ] = mu[ i ] * mu[ prime[ j ] ];
			}
		}
	}
}

long long f( const long long &X ){
	long long res = 0;
	long long d2;
	for ( long long d=2; d*d <= X; ++d ){
		d2 = d * d;
		if ( mu[d] < 0 )
			res -= (X / d2);
		else if ( mu[d] > 0 )
			res += (X / d2);
	}
	return -res;
}


int main(){
	sieve( 1000001 );
	
	int runs;
	long long N;
	long long l, r, m;

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%lld", &N);
		l = N - 1;
		r = UB;
		while ( r - l > 1 ){
			m = ( l + r ) >> 1;
			if ( f( m ) >= N )
				r = m;
			else
				l = m;
		}
		printf("%lld\n", r);
	}
	return 0;
}
