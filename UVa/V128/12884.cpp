#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<climits>
using namespace std;
const int MAXN = 1024;
typedef pair<long long, int> pli;
typedef pair<int,int> pii;
typedef pair< int, pii > node;

int N, P;
int M;
int X, Y;
vector<int> G[MAXN];
vector<int> W[MAXN];
long long D[2][MAXN][MAXN];
long long A[MAXN];
long long B[MAXN];
int U[MAXN];

void clean(){
	for ( int i=0; i < N; ++i ){
		U[i] = 0;
		G[i].clear();
		W[i].clear();
	}
}

void bellman(){
	// Initialize distances
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < N; ++j )
			D[1][i][j] = D[0][i][j] = LLONG_MAX;
	
	D[1][X][0] = 0;
	queue< node > q;
	q.push( node( 1, pii( X, 0 ) ) );

	int u, v, in, inV, w, len;
	long long d;
	while ( !q.empty() ){
		in = q.front().first;
		u = q.front().second.first;
		len = q.front().second.second;
		q.pop();
		
		d = D[in][u][len];
		for ( int i=0; i < (int)G[u].size(); ++i ){
			v = G[u][i], w = W[u][i];
			inV = in & U[v];
			if ( D[inV][v][len + 1] > w + d ){
				D[inV][v][len + 1] = w + d;
				if ( len + 1 < N ){
					q.push( node( inV, pii( v, len + 1 ) ) );
				}
			}
		}
	}
}

long long solve(){
	int x, y;
	
	for ( x = 1; x < N && A[x] == LLONG_MAX; ++x );
	for ( y = 1; y < N && B[y] == LLONG_MAX; ++y );
	if ( x == N ) return -1; 
	if ( x < y || (x == y && A[x] < B[y]) ) return LLONG_MAX;
	
	long long res = -1;
	long long num, den, tmp;
	for ( ; x < N ; ++x ){
		if ( A[x] < B[x] ){ // Otherwise A[x] is completely shadowed by B[x]
			// First look for the lines that have lower slope
			long long best = LLONG_MAX;
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
	while ( P-- ){
		scanf("%d %d %d", &u, &v, &w);
		u--, v--;
		G[u].push_back(v), G[v].push_back(u);
		W[u].push_back(w), W[v].push_back(w);
	}
	scanf("%d", &M);
	for ( int i=0; i < M; ++i ){
		scanf("%d", &u);
		U[u - 1] = 1;
	}

	bellman();
		
	for ( int i=1; i < N; ++i )
		A[i] = D[1][Y][i], B[i] = D[0][Y][i];

	// Find the best solution
	long long res = solve();
	if ( res == LLONG_MAX ) puts("Infinity");
	else if ( res < 0 ) puts("Impossible");
	else printf("%lld\n", res);
}

int main(){
	while ( scanf("%d %d %d %d", &N, &P, &X, &Y) != EOF ){
		process();
		clean();
	}
	return 0;
}
