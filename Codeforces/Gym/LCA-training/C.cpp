#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

const int MAXN = 100010;
const int NLOG = 18;

int L[MAXN];
int fst[MAXN];
int lg[2*MAXN];
vector<int> euler;
int log;
vector<int> T[MAXN];
vector< vector<int> > S;

void dfs( const int &u, const int &p ){
	int v;
	fst[u] = (int)euler.size();	
	euler.push_back(u);
	for ( int i = 0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		L[v] = L[u] + 1;
		dfs( v, u );
		euler.push_back( u );
	}
}

int RMQ( int l,  int r ){
	if ( r < l ) swap( l, r );
	int i = lg[r - l + 1];
	int u = S[i][l];
	int v = S[i][r - (1 << i) + 1];
	return L[u] < L[v]? u:v;
}

int main(){
	int N, M, Q;
	int u, v, a1, a2, a3, a4, x, y, z;	
	freopen ("lca_rmq.in", "r", stdin);
	freopen ("lca_rmq.out", "w", stdout);

	scanf("%d %d", &N, &Q);
	for ( int i = 1; i < N; ++i ){
		scanf("%d", &u);
		T[u].push_back(i);
	}
	// Precalc
	L[0] = 0;
	dfs( 0, -1 );
	M = (int)euler.size();
	for ( log = 0; (1 << log) <= M; ++log );
	log--;
	// precompute log of distance
	lg[1] = 0;
	for ( int i = 2; i <= M; ++i )
		lg[i] = lg[i / 2] + 1;
	// create sparse table
	S = vector< vector<int> > ( log + 1, vector<int>( M, 0 ) );
	
	for ( int i = 0; i < M; ++i )
		S[0][i] = euler[i];

	for ( int i = 1; i <= log; ++i ){
		for ( int j = 0; j + (1 << i) <= M; ++j ){
			u = S[i - 1][j], v = S[i - 1][j + (1 << (i - 1))];
			S[i][j] = ( L[u] < L[v] )? u:v;
		}
	}
	
	scanf("%d %d", &a1, &a2 );
	scanf("%d %d %d", &x, &y, &z);
	
	long long res = 0;
	v = 0;
	while ( Q-- ){
		v = RMQ( fst[(a1 + v) % N], fst[a2] );
		res += v;
		a3 = (int)((1LL * x * a1 + 1LL * y * a2 + z) % N);
		a4 = (int)((1LL * x * a2 + 1LL * y * a3 + z) % N);
		a1 = a3, a2 = a4;
	}
	printf("%lld\n", res);
	return 0;
}

