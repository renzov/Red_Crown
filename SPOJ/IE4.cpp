#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int MOD = 10007;
const int MAXN = 16;

int N;
long long fact[MOD + 5];
long long inv[MOD + 5];
int G[MAXN][MAXN];
long long W[MAXN][MAXN];
int indeg[MAXN];
int ord[MAXN];
int X[MAXN], Y[MAXN];

inline int bit( const int &x, const int &p ){
	return ( x >> p ) & 1;
}

void precalc(){
	fact[0] = fact[1] = 1;
	for ( int i=2; i < MOD; ++i )
		fact[i] = ( fact[i - 1] * i ) % MOD;
	
	long long temp[MOD + 5];
	temp[1] = 1;
	for ( int i = 2; i < MOD; ++i )
    	temp[i] = MOD - ( ( (MOD / i) * temp[MOD % i ] ) % MOD );
	
	for ( int i=0; i < MOD; ++i )
		inv[i] = temp[ fact[i] ];
}

bool reach( int x, int y ){
	if ( x < 0 || y < 0 ) return false;
	if ( x > y ) swap( x, y );
	if ( 2*x < y ) return false;
	if ( (x + y) % 3 ) return false;
	return true;
}

void topsort(){
	queue<int> q;
	for ( int i=0; i < N; ++i )
		if ( !indeg[i] ) q.push(i);
	
	int u;
	int t = 0; 
	while ( !q.empty() ){
		u = q.front(); 	q.pop();
		ord[ t++ ] = u;
		for ( int v=0; v < N; ++v ){
			if ( G[u][v] ){
				indeg[v]--;
				if ( !indeg[v] )
					q.push( v );
			}
		}
	}
}

long long nCm( const int &n, const int &m ){
	if ( m > n ) return 0LL;
	long long ans = ( fact[n] * inv[ m ] ) % MOD;
	return ( ans * inv[ n - m ] ) % MOD;
}

long long comb( const int &n, const int &m ){
	if ( m > n ) return 0LL;
	if ( m == 0 ) return 1LL;
	return ( comb( n / MOD, m / MOD ) * nCm( n % MOD, m % MOD ) ) % MOD;
}

void clean(){
	for ( int i=0; i < N; ++i ){
		indeg[i] = 0;
		fill( G[i], G[i] + N, 0 );
	}
}

long long solve( int cases ){
	long long res = 0LL;
	int A, B, R;
	int sum;
	// Adding the origin
	X[0] = Y[0] = 0;
	N = 1;

	scanf("%d %d %d", &A, &B, &R);
	A--, B--;

	for ( int i=0; i < R; ++i ){
		scanf("%d %d", X + N, Y + N );
		X[N]--,Y[N]--;
		if ( reach( X[N], Y[N] ) ){ 
			sum = (X[N] + Y[N]) / 3;
			X[N] -= sum, Y[N] -= sum;
			N++;
		}
	}

	if ( !reach( A, B ) ) return 0LL;	// no path possible
	if ( A == 0 && B == 0 ) return 1LL;	// origin == destination
	// Adding the destination
	X[N] = A, Y[N] = B; 
	sum = (A + B) / 3;
	X[N] -= sum, Y[N] -= sum;
	N++;	
	// Find a topological ordering of the points
	for ( int i=0; i < N; ++i ){
		for ( int j=i + 1; j < N; ++j ){
			if ( X[i] <= X[j] && Y[i] <= Y[j] ){
				G[i][j] = 1;
				indeg[j]++;
			}
			else if ( X[j] <= X[i] && Y[j] <= Y[i] ){
				G[j][i] = 1;
				indeg[i]++;
			}
		}
	}
	topsort();
	// Count the number of paths between reachable pairs
	int dx, dy;
	for ( int i=0; i < N; ++i )
		for ( int j=i+1; j < N; ++j )
			if ( G[i][j] ){
				dx = X[j] - X[i], dy = Y[j] - Y[i];
				W[i][j] = comb( dx + dy, dx );
			}
			else if ( G[j][i] ){
				dx = X[i] - X[j], dy = Y[i] - Y[j];
				W[j][i] = comb( dx + dy, dx );
			}
	// Apply inclusion-exclusion to find the number of paths
	int n = N - 2; // number of internal points
	long long ans;
	int last, idx;
	bool ok;
	int cnt;

	res = W[0][N - 1];
	for ( int mask=1; mask < (1 << n); ++mask ){
		last = 0; // the index of the origin
		ok = true;	// indicates if the mask is feasible
		cnt = 0;	// number of 1s in mask
		ans = 1LL;	// for the number of paths correspoding to mask
		for ( int i=0; ok && i < n; ++i ){
			if ( bit(mask, i) ){
				cnt++;
				idx = ord[i + 1];
				if ( G[last][ idx ] ){
					ans *= W[last][idx];
					ans %= MOD;
					last = idx;
				}
				else {
					ok = false;
				}
			}
		}
		if ( G[last][N - 1] ){
			ans *= W[last][N - 1];
			ans %= MOD;
		}
		else {
			ok = false;
		}
		if ( ok ){
			if ( cnt & 1 ){
				res = res + ( MOD - ans );
				res %= MOD;
			}
			else {
				res = res + ans;
				res %= MOD;
			}
		}
	}
	return res;
}

int main(){
	precalc();
	int runs, cases = 0;
	scanf("%d", &runs);
	while ( runs-- ){
		printf("Case #%d: %lld\n", ++cases, solve( cases ) );
		if ( runs ) clean();
	}
	return 0;
}
