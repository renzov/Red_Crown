#include<cstdio>
using namespace std;

int main(){
	long long A;
	int B;

	scanf("%lld %d", &A, &B);
	if ( A & 1 ) puts("0");
	else {
		long long res = 1LL;
		long long P = A >> 1;
		for ( int i=0; i < B; ++i ){
			res *= P;
			res %= A;
		}
		printf("%lld\n", res);
	}
	return 0;
}
