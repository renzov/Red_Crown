#include<cstdio>

int main(){

	int N, M, a, b;
	int res = 0; 
	scanf("%d %d", &N, &M);

	for ( a=0; a*a <= N; ++a ){
		b = N - a*a;
		if ( a + b*b == M ) res++;
	}	
	printf("%d\n", res);
	return 0;
}
