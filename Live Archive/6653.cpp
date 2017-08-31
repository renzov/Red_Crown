#include<cstdio>
using namespace std;
const long long MOD = 10000000000007LL;

int main(){
	int L, M, N;
	int runs;
	int cases = 0;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d %d", &L, &M, &N);
		long long res = 0;
		long long ant = 1;
		long long act;
		for ( int x=1; x <= N; ++x ){
			act = ant * ( L*L - x + 1 );
			act %= MOD;
			if ( x >= M )	res += act, res %= MOD;		
			ant = act;
		}
		printf("Case %d: %lld\n", ++cases, res);
	}
	return 0;
}

