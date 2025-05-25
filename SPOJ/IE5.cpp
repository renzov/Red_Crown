#include<cstdio>
using namespace std;
const int MAXM = 16;
const int MAXN = 305;
const int MOD = 9901;

int ans;
int X[MAXM];
int Y[MAXM];
int f[MAXN];
int deg[MAXN] = {0};
int pow2[MAXN];
int cycles[MAXN];

inline int find_set( const int &x ){ return ( x == f[x] )? x:( f[x] = find_set(f[x]) ); }
inline int bit( const int &S, const int &i ){ return (S >> i)&1; }

int fastpow( const int &base, const int &e ){
	if ( e == 0 ) return 1;
	if ( e == 1 ) return base;
	if ( e & 1 ) return ( fastpow( base, e - 1 ) * base ) % MOD;
	int temp = fastpow( base, e >> 1 );
	return ( temp * temp ) % MOD;
}

int count_cycles( const int &C, const int &Z ){
	int NZ = C - Z;	// number of nontrivial components (paths)
	int res = cycles[ C ];	// number of cycles in a complete graph with C vertices
	if ( C <= 2 ) NZ--;	// adjusting the counting
	if ( NZ > 0 ){		// for each nontrivial component we undo the contraction
		res *= pow2[ NZ ];
		res %= MOD;
	}
	return res;
}

void process(){
	int N, M;

	scanf("%d %d", &N, &M);
	for ( int i=0; i < M; ++i ){
		scanf("%d %d", X + i, Y + i);
		X[i]--, Y[i]--;
	}

	for ( int i=0; i < N; ++i ) f[i] = i;	// initialize for union-find

	bool ok, hamC;
	int u, v;
	int ru, rv;
	int C;
	int nzero;
	int value;

	ans = 0;
	for ( int mask = 0; mask < (1 << M); ++mask ){
		ok = true;
		hamC = false;
		C = N;	// number of components
		nzero = 0;	// number of vertices with degree > 0
		for ( int k=0; ok && k < M; ++k ){
			if ( bit(mask, k) ){
				u = X[k], v = Y[k];
				
				ru = find_set( u ); 
				rv = find_set( v );
				
				if ( ru == rv ){ 
					if ( C > 1 ) ok = false;	// set of edges contains a cycle but not hamiltonian
					else hamC = true;			// the set of edges contains a hamiltonian cycle
				}
				else { 
					f[rv] = ru; 
					C--; 
				}

				deg[ u ]++;
				if ( deg[u] == 1 ) nzero++; 
				deg[ v ]++;
				if (  deg[v] == 1 ) nzero++;
				if ( deg[u] > 2 || deg[v] > 2 ) // set of edges induce a vertex of degree greater than 3
					ok = false;
			}
		}

		if ( ok ){
			if ( hamC ) value = 1;
			else value = count_cycles( C, N - nzero );
			
			if ( __builtin_popcount( mask ) & 1 ){
				ans += ( MOD - value );
				ans %= MOD;
			}
			else {
				ans += value;
				ans %= MOD;
			}
		}
		// initiate data structures for next iteration
		for ( int k=0; k < M; ++k ){
			if ( bit(mask, k) ){
				u = X[k], v = Y[k];
				deg[u] = deg[v] = 0;
				f[u] = u, f[v] = v;
			}
		}
	}
}

void precalc(){
	pow2[0] = 1;
	for ( int i = 1; i < 301; ++i ){
		pow2[i] = (pow2[i - 1] << 1) % MOD;
	}
	cycles[0] = 0; cycles[1] = cycles[2] = 1;
	int fact = 1;
	int inv = fastpow( 2, MOD - 2 );
	for ( int i=3; i < 301; ++i ){
		fact *= (i - 1);
		fact %= MOD;
		cycles[i] = (fact * inv) % MOD;
	}
}

int main(){

	int runs;
	int cases = 0;

	precalc();

	scanf("%d", &runs);
	while ( runs-- ){
		cases++;
		process();
		printf("Case #%d: %d\n", cases, ans);
	} 
	return 0;
}
