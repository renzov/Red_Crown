#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 64;
const long long MOD = 1000000007LL;

int N;
bool G[MAXN][MAXN];
int dfsnum[MAXN];
int num;
int P[MAXN];	// P[i] = number of paths of length i
int C[MAXN];	// C[i] = number of cycles of length i

int cntV;
int cntE;

long long fact[MAXN];
long long inv[MAXN];

long long fast_pow( const long long &A, const long long &p ){
	if ( p == 0 ) return 1LL;
	if ( p == 1 ) return A % MOD;
	long long t = ( p & 1 )? fast_pow(A, p - 1 ):fast_pow( A, p >> 1 );
	if ( p & 1 ) return ( A * t ) % MOD;
	return ( t * t ) % MOD;
}

void preprocess(){
	fact[0] = fact[1] = 1;
	inv[0] = inv[1] = 1;
	for ( int i=2; i <= 50; ++i ){
		fact[i] = (i * fact[i - 1]) % MOD;
		inv[i] = fast_pow( fact[i], MOD - 2 );
	}
}

void dfs( const int &u, const int &p ){
	cntV++;
	dfsnum[u] = num++;

	for ( int v = 0; v < N; ++v ){
		if ( v == u || v == p ) continue;
		if ( G[u][v] ){
			if ( dfsnum[v] == -1 ){
				cntE++;
				dfs(v, u);
			}
			else if ( dfsnum[v] < dfsnum[u] ){
				cntE++;
			}
		}
	}
}

void process(){
	char adj[MAXN];

	scanf("%d", &N);

	fill( dfsnum, dfsnum + N, -1 );
	fill( P, P + (N + 1), 0 );
	fill( C, C + (N + 1), 0 );

	for ( int i=0; i < N; ++i ){
		scanf("%s", adj);
		for ( int j=0; j < N; ++j ){
			if ( i == j ) G[i][j] = false;
			G[i][j] = adj[j] == '0'? true:false;
		}
	}

	num = 0;
	for ( int i=0; i < N; ++i )
		if ( dfsnum[i]  == -1 ){
			cntV = cntE = 0;
			dfs( i, -1 );
			if ( cntE == cntV ) C[ cntV ]++;
			else P[ cntV ]++;
		}
	
	// Counting part
	long long res = fact[N];
	long long den;
	res = (res * inv[ fact[ P[1] ] ]) % MOD;
	for ( int i=2; i <= N; ++i ){
		res = ( res * inv[ fact[ P[i] ] ] ) % MOD;
		res = ( res * inv[ fact[ C[i] ] ] ) % MOD;
		den = fast_pow( 2*i, C[i] );
		den = fast_pow( den, MOD - 2 );	// Calculating inverse
		res = ( res * den ) % MOD;
		den = fast_pow( 2, P[i] );
		den = fast_pow( den, MOD - 2 );	// Calculating inverse
		res = ( res * den ) % MOD;		
	}
	printf("%lld\n", res);
}

int main(){
	int runs;

	preprocess();
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}
