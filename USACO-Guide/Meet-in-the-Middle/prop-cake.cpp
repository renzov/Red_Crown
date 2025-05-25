#include<cstdio>
#include<climits>
#include<vector>
#include<algorithm>
using namespace std;

typedef pair<int, int> pii;

const int MAXN = 42;
int N, P, Q;
int X[MAXN], Y[MAXN], Z[MAXN];
int ans;

vector<pii> L[MAXN][MAXN];
vector<pii> R[MAXN][MAXN];

void get_all_subsets( const int &b, const int &size, vector<pii> C[MAXN][MAXN] ){
	int x, y, z;
	for ( int mask = 1; mask < (1 << size); ++mask ){
		x = y = z = 0;
		for ( int i = 0; i < size; ++i )
			if ( (mask >> i) & 1 ){
				x += X[b + i];
				y += Y[b + i];
				z += Z[b + i];
			}
		// Check if this subset is a solution	
		if ( ( (x / P) == (y / Q) ) && !(x % P) && !(y % Q) ){
			ans = min( ans, z );
		}

		C[x % P][y % Q].push_back( pii( x/P - y/Q, z ) );
	}
	// sort the tuples
	for ( int i = 0; i < P; ++i )
		for ( int j = 0; j < Q; ++j )
			sort( C[i][j].begin(), C[i][j].end() );
}

int main(){

	scanf("%d %d %d", &N, &P, &Q);
	
	int g = __gcd( P, Q );
	P /= g, Q /= g;			// Make P and Q relatively prime -- not assured by statement

	for ( int i = 0; i < N; ++i )
		scanf("%d %d %d", X + i, Y + i, Z + i );
	
	int n = N >> 1;
	int m = N - n;
	ans = INT_MAX;

	get_all_subsets( 0, n, L );
	get_all_subsets( n, m, R );

	vector<pii>::iterator E, F;
	int ni, nj, nk;

	for ( int i = 0; i < P; ++i )
		for ( int j = 0; j < Q; ++j )
			for ( E = L[i][j].begin(); E != L[i][j].end(); ++E ){
				ni = (P - i) % P, nj = (Q - j) % Q;
				nk = -E->first;
				F = lower_bound( R[ni][nj].begin(), R[ni][nj].end(), pii( nk, INT_MIN ) );
				if ( F != R[ni][nj].end() && F->first == nk )
					ans = min( ans, E->second + F->second );
			}
	
	if ( ans == INT_MAX ) puts("-1");
	else printf("%d\n", ans );
	return 0;
}
