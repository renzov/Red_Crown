#include<cstdio>
#include<algorithm>
using namespace std;

int main(){
	int K;
	scanf("%d", &K);
	
	int d = 1;
	int a, b;

	for ( int i = 2; i <= K/i; ++i ){
		if ( K % i == 0 ){
			a = i;
			b = K / i;
			if ( 2 * a < K ) d = max( d, a );
			if ( 2 * b < K ) d = max( d, b );
		}
	}
	int L = K / d - 1;
	printf("%d\n", L);
	return 0;
}
