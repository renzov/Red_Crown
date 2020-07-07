#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 1024;
const int MAXM = 10005;
const long long INF = 1LL << 60;
typedef pair<long long, int> pli;
typedef pair<int,int> pii;
typedef pair< int, pii > node;

int N, P;
int M;
int X, Y;

int U[MAXM];
int V[MAXM];
int W[MAXM];
int S[MAXN];


long long D[2][MAXN][MAXN];
long long A[MAXN];
long long B[MAXN];

void bellman(){
	// Initialize distances
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < N; ++j )
			D[1][i][j] = D[0][i][j] = INF;
	
	D[1][X][0] = 0;

	int u, v, w;

	for ( int len = 1; len < N; ++len ){
		for ( int e = 0; e < P; ++e  ){
			u = U[e], v = V[e], w = W[e];
			if ( S[u] && S[v] ){
				D[1][u][len] = min( D[1][u][len], D[1][v][len - 1] + w );
				D[1][v][len] = min( D[1][v][len], D[1][u][len - 1] + w );
			}
			D[0][u][len] = min( D[0][u][len], D[0][v][len - 1] + w );
			D[0][v][len] = min( D[0][v][len], D[0][u][len - 1] + w );
			if ( !S[u] ){
				D[0][u][len] = min( D[0][u][len], D[1][v][len - 1] + w );
			}
			if ( !S[v] ){
				D[0][v][len] = min( D[0][v][len], D[1][u][len - 1] + w );
			}
		}
	}

}

long long solve(){
	int x, y;
	
	for ( x = 1; x < N && A[x] == INF; ++x );
	for ( y = 1; y < N && B[y] == INF; ++y );
	if ( x == N ) return -1; 
	if ( x < y || (x == y && A[x] < B[y]) ) return INF;
	
	long long res = -1;
	long long num, den, tmp;
	for ( ; x < N ; ++x ){
		if ( A[x] < B[x] ){ // Otherwise A[x] is completely shadowed by B[x]
			// First look for the lines that have lower slope
			long long best = INF;
			for ( int j=1; j < x; ++j ){
				if ( B[j] <= A[x] ){	// A[x] is useless
					best = -1; break;
				}
				// Find upper bound for increment
				num = B[j] - A[x]; 
				den = x - j;
				best = min( best, num/den - (num % den == 0) );
			}
			// Now, check the lines with greater slope
			if ( best >= 0 ){ // If best <= 0 already this check is useless
				for ( int j=x + 1; j < N; ++j ){
					if ( B[j] < A[x] ){ // Otherwise A[x] dominates B[j] completely
						// Find the lower bound
						num = A[x] - B[j];
						den = j - x;
						tmp = num / den + ( num % den == 0 );
						if ( best < tmp ){ // Lower bound in infeasible
							best = -1;
							break;
						}
					}
				}
			}
			res = max( res , best );
		}
	} 
	return res;
}

void process(){
	int u, v, w;
	// Zero-indexed vertices
	X--, Y--;
	for ( int i=0; i < P; ++i ){
		scanf("%d %d %d", U + i, V + i, W + i );
		U[i]--, V[i]--;
	}
	scanf("%d", &M);
	for ( int i=0; i < M; ++i ){
		scanf("%d", &u);
		S[u - 1] = 1;
	}

	bellman();
		
	for ( int i=1; i < N; ++i )
		A[i] = D[1][Y][i], B[i] = D[0][Y][i];

	// Find the best solution
	long long res = solve();
	if ( res == INF ) puts("Infinity");
	else if ( res < 0 ) puts("Impossible");
	else printf("%lld\n", res);
}

int main(){
	while ( scanf("%d %d %d %d", &N, &P, &X, &Y) != EOF ){
		process();
		fill( S, S + N, 0 );
	}
	return 0;
}

