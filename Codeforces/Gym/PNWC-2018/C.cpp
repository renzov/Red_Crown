#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 1024;
const long long MOD = 998244353LL;

int N, K;
int D[MAXN];
int V[MAXN];
int C[MAXN];
long long f[MAXN][MAXN];

long long solve( const int &n, const int &k ){
	if ( k == 0 ) return 1LL;
	if ( n >= N ) return k == 0? 1:0; 
	long long &res = f[n][k];
	if ( res != -1 ) return res;
	res = 0LL;
	res = solve( n + 1, k  - 1 ) * C[n];
	res %= MOD;
	res += solve( n + 1, k );
	res %= MOD;
	return res;
}

int main(){

	scanf("%d %d", &N, &K);
	for ( int i=0; i < N; ++i )
		scanf("%d", D + i );
	
	sort( D , D + N );
	
	int last = D[0];
	int cnt = 0;
	int p = 0;
	
	for ( int i=0; i < N; ++i ){
		if ( D[i] == last ) cnt++;
		else {
			V[p] = last, C[p] = cnt; p++;
			cnt = 1, last = D[i];
		}
	}
	V[p] = last, C[p] = cnt; p++;
	N = p;

	if ( N < K ){ 
		puts("0");
	}
	else { 
		for ( int i=0; i < N; ++i )
			fill( f[i], f[i] + (K + 1), -1 );
		printf("%lld\n", solve( 0, K ) );
	}
	return 0;
}
