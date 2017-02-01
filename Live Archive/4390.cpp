#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

const int MAXN = 500000;
int rev[MAXN + 2];
int lastp[MAXN + 2] = {0};
int prime[MAXN + 2];
int coef[MAXN + 2] = {0};
int P = 0;
int f[MAXN+2];
int size[MAXN+2];
int M;
int N;

void sieve(){
	rev[2] = 0;
	prime[P++] = 2;
	for ( int i=3; i <= 707  ; i+= 2 ){
		if ( !lastp[i] ){
			rev[ i ] = P;
			prime[P++] = i;
			lastp[i] = i;
			for ( int j=i*i; j < MAXN ; j += (i<<1) )
				lastp[j] = i;
		}
	}
	for ( int i=709; i < MAXN; i+= 2 ) 
		if ( !lastp[i] ){ 
			rev[ i ] = P;
			prime[P++] = i;
			lastp[i] = i;
		}
}

int main(){
	sieve();
	int runs;
	int idx;
	int n,t;
	long long temp;

	scanf("%d",&runs);
	while (runs--){
		scanf("%d %d", &N, &M);
		fill( coef , coef + P, 0 );
		idx = 0;
		n = N-1;
		/* coef[i] = 0 for i=0 ... P-1 */
		while ( idx < P && prime[idx] <= n ){ /* Calculating for each prime the coeficient in N-1! */
			temp = prime[idx];
			while ( n >= temp ){ 
				coef[idx] += (int)(n / temp); /* floor( N-1 / p^x ) */
				temp *= prime[idx];
			}
			idx++;
		}
		/* idx = index of prime s.t. prime[idx-1] <= N-1 < prime[idx] or idx = P */
		for ( int i=0; i < n; ++i ){
			scanf("%d", &t); t--;
			f[ i + 1  ] = t;
	        size[i] = 1;	
		}
		size[n] = 1;
		for ( int i=n; i >= 0; i-- ){
			size[ f[i] ] += size[ i ];
		}
		int last;
		for ( int i=1; i < N; ++i ){
			last = size[i];
			/* factorize number last and update coef[...] */
			while ( !(last & 1) ){ /* coeficient of 2 */
				coef[0]--;
				last >>= 1;
			}
			/* last must be odd number */
			while ( last > 1 ){ /* factorize using lastp[...] */
				coef[ rev[lastp[last]] ]--;
				last /= lastp[last];
			}
		}
		long long res = 1;
		/* calculate result */
		for ( int i=0; i < idx; ++i ) /* remember value of idx */
			for ( int j=0; j < coef[i]; ++j ){
				res *= prime[i];
				res %= M;
			}
		printf("%lld\n", res);
	}
	return 0;
}

