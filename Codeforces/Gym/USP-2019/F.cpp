#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;

int main(){

	long long A, B;
	long long res;

	scanf("%lld %lld", &A, &B);
	B /= __gcd( A, B );
	
	res = 1;
	for ( long long p = 2; p * p * p <= B; ++p ){
		if ( B % p == 0 ){
			res *= p;
			do {
				B /= p;
			}
			while ( B % p == 0 );
		}
	}
	
	long long sq = sqrt( B );
	if ( sq * sq == B ){
		res *= sq;
	}
	else {
		res *= B;
	}
	printf("%lld\n", max( 2LL, res ));
	return 0;
}
