#include<cstdio>
using namespace std;

int main(){
	int N, K;

	scanf("%d %d", &N, &K);

	long long preMod = 0;
	long long pow10;
	int ans = 0;

	for ( int i = 1; i <= N; ++i ){
		pow10 = 1;	
		while ( pow10 <= i )
			pow10 *= 10;
		
		preMod = ( preMod * ( pow10 % K ) ) % K;
		preMod = ( preMod + i ) % K;
		if ( !preMod ) ans++;
	}
	printf("%d\n", ans );
	return 0;
}
