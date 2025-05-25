#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN = 32;

int N, M;
long long A[MAXN][MAXN];
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

int b;	// offset to access the direction array (dx, dy) 
vector<long long> L[MAXN];
vector<long long> R[MAXN];
long long elim[MAXN];	// element of the A in the diagonal -- to eliminate duplicate counting

void sort_sol( vector<long long> res[] ){
	for ( int i = 0; i < min(N, M); ++i )
		sort( res[i].begin(), res[i].end() );
}

inline bool valid( const int &x, const int &y ){
	return x >= 0 && y >= 0 && x < N && y < M;
}

void gen_paths( const int &x, const int &y, const int &n, const long long &sum, vector<long long> res[] ){
	if ( !n ){
		if ( N <= M ){
			res[x].push_back( sum );
			elim[x] = A[x][y];
		}
		else {
			res[y].push_back( sum );
			elim[y] = A[x][y];
		}
		return;
	}
	
	int nx, ny;

	nx = x + dx[b], ny = y + dy[b];
	if ( valid(nx, ny) )
		gen_paths( nx, ny, n - 1, sum ^ A[nx][ny], res );
	
	nx = x + dx[b + 1], ny = y + dy[b + 1];
	if ( valid(nx, ny) )
		gen_paths( nx, ny, n - 1, sum ^ A[nx][ny], res );
}

int main(){
	long long K;

	scanf("%d %d %lld\n", &N, &M, &K);
	// Read the matrix
	for ( int i = 0; i < N; ++i )
		for ( int j = 0; j < M; ++j )
			scanf("%lld", A[i] + j );
	
	int nsteps = N + M - 2;	// # of moves to reach the end
	int n = nsteps >> 1;
	int m = nsteps - n;
	// find all downward paths of length n -- starting from (0, 0)
	b = 0;
	gen_paths( 0, 0, n, A[0][0], L );
	sort_sol( L );
	// find all upward paths of length m -- starting from (N - 1, M - 1)
	b = 2;
	gen_paths( N - 1, M - 1, m, A[N - 1][M - 1], R );
	sort_sol( R );
	// combine the solutions
	long long ans = 0LL;
	long long val;
	vector<long long>::iterator lp, rp;

	for ( int i = 0; i < min(N, M); ++i ){
		for ( int j = 0; j < (int)L[i].size(); ++j ){
			val = L[i][j] ^ elim[i] ^ K;
			lp = lower_bound( R[i].begin(), R[i].end(), val );
			rp = upper_bound( R[i].begin(), R[i].end(), val );
			ans += distance( lp, rp );
		}
	}
	printf("%lld\n", ans);
	return 0;
}
