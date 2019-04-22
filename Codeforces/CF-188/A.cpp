#include<cstdio>
int main(){

	long long N, K;

	scanf("%I64d %I64d", &N, &K);
	long long odds = (N + 1) >> 1;
	if ( K <= odds ) printf("%I64d\n", (K<<1) - 1);
	else printf("%I64d\n", (K - odds) << 1);
	return 0;
}
