/* Error in test data, should suppose that m <= LLONG_MAX */
#include <cstdio>
using namespace std;

const int MAXN = 25;
const int MAXL = 50;

int f[MAXN + 2];
int primeF[MAXL + 2] = {0};
int coef[MAXL + 2][MAXL + 2] = {0};
int coef2[MAXL + 2][MAXL + 2] = {0};
int N;

void sieve(){
	for ( int i=2; i <= MAXL; i+= 2 ) primeF[i] = 2;
	for ( int i=3; i <= MAXL; i += 2 ){
		if ( !primeF[i] ){
			primeF[i] = i;
			for ( int j=i*i; j <= MAXL; j += (i << 1) ){
				primeF[j] = i;
			}
		}
	}
}

void precomp(){
	for ( int i=2; i <= MAXL; ++i )
		coef[0][i] = coef[1][i] = 0;
	
	int temp;
	for ( int i=2; i <= MAXL; ++i ){
		for ( int j=2; j <= i; ++j )
			coef[i][j] = coef[i-1][j];	
		/* Factorize i */
		temp = i;
		while ( temp > 1 ){
			coef[i][ primeF[temp] ]++;
			temp /= primeF[temp];
		}
	}
}

long long computeM( int L ){
	int c[MAXL + 2] = {0};
	int t;

	for ( int i=2; i <= L; ++i )
		c[i] = coef[L][i];

	for ( int j=0; j < N; ++j ){
		t = f[j];
		if ( t ){
			for ( int i=2; i <= t; ++i )
				c[i] -= coef[ t ][ i ];
		}
	}

	long long res = 1;
	for ( int i=2; i <= L; ++i )
		for ( int j=0; j < c[i]; ++j ){
			res *= i;
		}
	
	return res;
}

int main(){
	int L;
	long long total, temp;
	long long K;
	bool ok;
	sieve();
	precomp();

	while ( scanf("%d %lld", &N, &K) && N ){
		L = 0;
		for ( int i=0; i < N; ++i ){
			scanf("%d", f+i);
			L += f[i];
		}
		total = computeM( L );
		for ( int i=L-1; i > 0; --i ){
			temp = total;
			ok = false;
			for ( int j=0; j < N && !ok; ++j ){
				// Test for the j-th character
				if ( f[j] > 0 ){
					f[j]--;
					temp = computeM( i );
					if ( temp > K ){
						printf("%c", (char)(j+'a'));
						total = temp;
						ok = true;
					}
					else {
						f[j]++;
						K -= temp;
						temp = total;
					}
				}
			}
		}
		for ( int i=0; i < N; ++i )
			if (f[i] > 0){ 
				printf("%c\n", (char)(i+'a'));
				break;
			}
	}
	return 0;
}

