#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXP = 1000000; 
long long primes[MAXP + 5];
int f[MAXP + 5];
bool np[MAXP + 5] = {0};
int M;

void precalc(){
	M = 0;
	primes[M++] = 2;
	int i;
	for ( i=3; i*i < MAXP; i += 2 ){
		if ( !np[i] ){
			primes[M++] = i;
			for ( int j=i*i; j < MAXP; j += (i << 1) )
				np[j] = true;
		}
	}
	for ( ; i < MAXP ; i += 2 )
		if ( !np[i] )
			primes[M++] = i;
}

inline int find_set( const int &x ){
	return ( x != f[x] )? ( f[x] = find_set(f[x]) ):x;
}

int main(){
	precalc(); // Find the primes til 10^6
	int runs;
	int cases = 0;
	long long L, R, P;
	
	scanf("%d", &runs);
	while ( runs-- ){
		cases++;
		scanf("%lld %lld %lld", &L, &R, &P);
		// make the sets
		for ( int i=0; i < (R - L + 1); ++i )
			f[i] = i;
		int res = R - L + 1;
		int first = lower_bound( primes, primes + M, P ) - primes;
		long long pr , base;
		int s1, s2;
		for ( int i=first; i < M; ++i ){
			pr = primes[i];
			base = (L / pr)*pr;
			if (base < L) base += pr;
			s1 = find_set( base - L );
			for ( int act=base + pr; act <= R; act += pr ){
				s2 = find_set(act - L);	
				if ( s1 != s2 ){ //join set
					f[s2] = s1;
					res--;
				} 
			}	
		}
		printf("Case #%d: %d\n", cases, res);
	}

	return 0;
}
