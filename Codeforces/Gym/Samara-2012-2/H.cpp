#include<cstdio>
#include<algorithm>
using namespace std;

int main(){
	int N; 

	scanf("%d", &N);
	
	int M = 0;
	int a; 
	for ( int i = 0; i < N; ++i ){
		scanf("%d", &a);
		M = max( a, M );
	}
	if ( M == 1 ) puts("Mike");
	else if ( M == 2 ) puts("Constantine");
	else {
		M++;
		if ( __builtin_popcount(M) == 1 ) puts("Mike");
		else puts("Constantine");
	}
	return 0;
}
