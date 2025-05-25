#include<cstdio>
using namespace std;

int main(){

	long long N;
	long long res;
	long long diff;
	int T;
	int p;

	scanf("%d", &T);
	while ( T-- ){

		scanf("%lld", &N);

		res = ( N * (N + 1) )>> 1;
		p = 0;
		while ( (1LL << p) <= N ) p++;
		diff = ( 1LL << p ) - 1;
		
		printf("%lld\n", res - (diff << 1));
	}
	return 0;
}
