#include <cstdio>

using namespace std;

typedef long long int64;
typedef long double ldouble;

const int MAXN = 1000005;
int phi[MAXN];
int div[MAXN] = {0};
int64 res[MAXN] = {0};

void sieve(){
	phi[1] = 1;
	for ( int i=4; i <= 1000000; i+= 2 ) div[i] = 2;
	for ( int i=3; i <= 1000; i += 2 ){
		if ( !div[i] ){
			for ( int j=i*i; j <= 1000000; j += (i<<1) ){
				div[j] = i;
			}
		}
	}
	for ( int i=2; i <= 1000000; ++i ){
		if ( !div[i] ) phi[i] = i-1;
		else if ( (i / div[i]) % div[i] ){
			phi[i] = phi[i/div[i]] * (div[i]-1);
		}
		else {
			phi[i] = phi[i/div[i]]*div[i];
		}
	}
}

int main(){
	sieve();
	for ( int i=1; i <= 1000000; ++i ){
		for ( int j=i; j <= 1000000; j += i ){
			res[j] += (1LL * phi[i] * i);
		}
	}
	for (int i=2; i <= 1000000; ++i){
		res[i]++;
		res[i] *= i;
		res[i] >>= 1;
	}
	res[1] = 1;
	int runs;
	int N;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &N);
		printf("%lld\n", res[N]);
	}
	return 0;
}
