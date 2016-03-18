#include <cstdio>

const int MAXN = 4000001;

int div[MAXN] = {0};
int phi[MAXN];
long long res[MAXN];

void sieve(){
	for ( int i=4; i < MAXN; i+=2 ) div[i] = 2;
	phi[2] = 1;
	for ( int i=3; i < MAXN; i++ ){
		if ( !div[i] ){
			phi[i] = i - 1;
			if ( i <= 2000 ){
				for ( int j=i*i; j < MAXN; j += 2*i ){
					div[j] = i;
				}
			}
		}
		else if ( !((i / div[i]) % div[i]) ){
			phi[i] = div[i] * phi[ i / div[i] ];
		}
		else {
			phi[i] = (div[i] - 1) * phi[ i / div[i] ];
		}
	}
}

int main(){
	int N;
	sieve();
	res[0] = res[1] = 0;
	for ( int i=2; i < MAXN; ++i ) res[i] = phi[i];
	for ( int i=2; i < MAXN; ++i ){
		for ( int j=2*i; j < MAXN; j+= i ){
			res[j] += i * phi[j/i];
		}
	}
	for ( int i=2; i < MAXN; ++i )
		res[i] += res[i-1];
	while ( scanf("%d", &N) && N > 1 ){
		printf("%lld\n", res[N]);
	}
	return 0;
}

