#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN = 10000005;

bool composite[MAXN];
int mu[MAXN];
vector<long long> primes;
long long res;
long long M;
long long A, B, C, D;

void sieve (long long n){
	mu[1] = 1;
	for (long long i = 2; i <= n; ++i){
		if (!composite[i]) primes.push_back(i), mu[i] = -1;
		for (int j = 0; j < primes.size() && i * primes[j] <= n; ++j) {
			composite[ i * primes[j] ] = true;
			if (i % primes[j] == 0){ 
				mu[ i * primes[j] ] = 0;
				break;
			}
			else {
				mu[ i * primes[j] ] = mu[i] * mu[ primes[j] ];
			}
		}
	}
}

int main(){
	scanf("%lld %lld %lld %lld", &A, &B, &C, &D);
	M = max( C, D );
	sieve( M );
	// Inclusion-Exclusion
	res = 0;
	long long X, Y;
	for ( int i=1; i <= M; ++i ){
		X = (B / i) - ((A - 1) / i);
		Y = (D / i) - ((C - 1) / i);
		res += (mu[i] * X * Y);
	}
	printf("%lld\n", res);
	return 0;
}
