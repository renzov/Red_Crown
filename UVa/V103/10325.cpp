#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXM = 16;
int N, M;
int V[MAXM];

long long LCM( const int &mask ){
	long long res = 1;
	long long g;
	for ( int i=0; i < M; ++i )
		if ( (mask >> i)&1 ){
			g = __gcd( res, (long long)V[i] );
			res = ( res * V[i] ) / g;
		}
	return res;
}

void process(){
	for ( int i=0; i < M; ++i )
		scanf("%d", V + i);
	sort( V, V + M );
	M = unique( V, V + M ) - V;

	long long res = 0;
	long long div;
	long long l;
	for ( int i=1; i < (1 << M); ++i ){
		l = LCM( i );
		div = N / l;
		if ( __builtin_popcount( i ) & 1 )
			res += div;
		else 
			res -= div;
	}
	printf("%lld\n", N - res);
}


int main(){
	while ( scanf("%d %d", &N, &M) == 2 )
		process();
	return 0;
}
