#include<cstdio>
using namespace std;

int main(){
	int N;
	int k;
	scanf("%d", &N);

	int res = 0;

	for ( int i=1; i <= N; ++i )
		for ( int j=i; j <= N/i; ++j ){
			k = N / ( i * j );
			if ( N % ( i * j ) == 0 && k >= j ){ 
				res++;
			}
		}
	printf("%d\n", res);
	return 0;
}
