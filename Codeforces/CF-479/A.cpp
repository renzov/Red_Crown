#include<cstdio>
using namespace std;

int main(){
	int N, K;
	scanf("%d %d", &N, &K);
	while ( K-- )
		if ( N % 10 || N < 10 )
			N--;
		else 
			N /= 10;
	printf("%d\n", N);
	return 0;
}
