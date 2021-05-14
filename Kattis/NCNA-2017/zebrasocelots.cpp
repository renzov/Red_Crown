#include<cstdio>
using namespace std;

int main(){
	int N;
	char c;
	long long res = 0;

	scanf("%d", &N);
	for ( int i=N - 1; i >= 0; --i ){
		scanf(" %c", &c);
		if ( c == 'O' )
			res |= ( 1LL << i );
	}
	printf("%lld\n", res);
	return 0;
}
