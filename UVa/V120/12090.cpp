#include<cstdio>
#include<cassert>
using namespace std;

int primes[1000005];
bool np[3162279] = {0};
int M = 0;
int coef[64];

void precalc(){
	primes[M++] = 2;
	for ( int i=3; i <= 3162277; i += 2 ){
		if ( !np[i] ){ 
			primes[M++] = i;
			for ( long long j=1LL*i*i; j <= 3162277; j += (i << 1) )
				np[j] = true;
		}
	}
}

int main(){
	precalc();
	long long N;
	int L;
	int x;
	long long tmp;
	while ( scanf("%lld", &N) && N ){
		tmp = N;
		L = 0; 
		for ( int i=0; i < M && N >= primes[M]; ++i )
			if ( N % primes[i] == 0 ){
				x = primes[i];
				coef[L] = 1;
				N /= x;
				while ( N % x == 0 )
					N /= x, coef[L]++;
				L++;
			}
		if ( N > 1 ){ // It is a prime number
			coef[L++] = 1;
		}
		int res = 0;
		int cnt;
		bool allzero;
		int pot = 1;
		do {
			allzero = true;
			cnt = 1;
			for ( int i=0; i < L; ++i ){
				if ( coef[i] / pot ){ // Check if it is different from zero
					cnt *= ( 1 + coef[i]/pot );
					if ( coef[i] / ( pot + 1 ) ) allzero = false;
				}
			}
			res += cnt;
			if ( !allzero ) pot++;
		}
		while ( !allzero );
		res -= pot;
		printf("%lld %d\n", tmp, res);
	}
	return 0;
}
