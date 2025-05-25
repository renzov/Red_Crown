#include<cstdio>
using namespace std;
const int MAXN = 32;

char A[MAXN];
char B[MAXN];

int main(){

	int N;

	scanf("%d %s %s", &N, A, B);
	
	int res = 1;
	for ( int i=0; i < N; ++i )
		if ( A[i] != B[i] ) res <<= 1;
	printf("%d\n", res);
	return 0;
}
