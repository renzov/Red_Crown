#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int MAXN = 40005;
const int LOGN = 17;

int N, Q;
vector<int> A[MAXN];
vector<int> B[MAXN];
int fA[MAXN];
int fB[MAXN];
int lA[MAXN];
int lB[MAXN];
int PA[LOGN][MAXN];
int PB[LOGN][MAXN];
int diamA[MAXN];
int diamB[MAXN];
long long S[MAXN];

void read_tree( vector<int> G[MAXN], const int &n ){
	int u, v;
	for ( int i=1; i < n; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		G[u].push_back(v), G[v].push_back(u);
	}
}

int dfs( vector<int> G[], int l[], int f[], const int &u, const int &p ){
	f[u] = p;
	l[u] = ( p == -1 )? 0:(l[p] + 1);
	int v, w;
	int res = u;
	for ( int i=0; i < (int) G[u].size(); ++i ){
		v = G[u][i];
		if ( v != p ){ 
			w = dfs( G, l , f, v, u );
			if ( l[w] > l[res] ) res = w;
		}
	}
	return res;
}

void preprocess( int P[LOGN][MAXN], int l[], int f[], const int &n ){
	int log; 
	for ( log=0; (1 << log) <= n; log++ ); log--;
	// Initialize the dp
	for ( int i=0; i < n; ++i ) P[0][i] = f[i];
	for ( int j=1; j <= log; ++j )	
		for ( int i=0; i < n; ++i )
			P[j][i] = -1;
	// Process the dp
	for ( int j=1; j <= log; ++j )
		for ( int i=0; i < n; ++i )
			if ( P[j-1][i] != -1 )
				P[j][i] = P[j-1][ P[j-1][i] ]; 			
}

int lca( int P[LOGN][MAXN], int l[], int u, int v, const int &n ){
	if ( u == v ) return u;
	if ( l[u] > l[v] ) swap( u, v );
	// printf("u = %d - v = %d\n", u, v);
	int log;
	for ( log=0; (1 << log) <= n; ++log ); log--;
	for ( int i=log; i >= 0; --i )
		if ( (1 << i) <= (l[v] - l[u]) )
			v = P[i][v];
	// printf("after lifting - v = %d\n", v);
	if ( u == v ) return u;
	for ( int i=log; i >= 0; --i )
		if ( P[i][u] != P[i][v] )	// Remember that u and v are always in the same level
			u = P[i][u], v = P[i][v];
	return P[0][u];
}

void process(){
	// Read both trees
	read_tree( A, N );
	read_tree( B, Q );
	// Calculate parent, level info
	int a1, a2;	// diameter of A
	int b1, b2;	// diameter of B
	a1 = dfs( A, lA, fA,  0, -1 );
	b1 = dfs( B, lB, fB, 0 , -1 );
	a2 = dfs( A, lA, fA, a1, -1 );
	b2 = dfs( B, lB, fB, b1, -1 );
	// Preprocess the trees to find LCA
	preprocess( PA, lA, fA, N );
	preprocess( PB, lB, fB, Q );
	// Find the longest path for each vertex in each tree
	int u, v;
	for ( int i=0; i < N; ++i ){
		u = lca( PA, lA, i, a1, N ), v = lca( PA, lA, i, a2, N );
		diamA[i] = max( lA[i] + lA[a1] - 2*lA[u] , lA[i] + lA[a2] - 2*lA[v] );
	}
	for ( int i=0; i < Q; ++i ){
		u = lca( PB, lB, i, b1, Q ), v = lca( PB, lB, i, b2, Q );
		diamB[i] = max( lB[i] + lB[b1] - 2*lB[u] , lB[i] + lB[b2] - 2*lB[v] );
	}
		
	long long D = max( diamA[a2], diamB[b2] );
	int idx;
	sort( diamB, diamB + Q );
	// 	Find suffix sum on the diameters
	S[Q] = 0;
	for ( int i=Q-1; i >= 0; --i ) 
		S[i] = S[i + 1] + diamB[ i ];
	
	long long res = 0;
	for ( int i=0; i < N; ++i ){
		idx = lower_bound( diamB, diamB + Q, D - diamA[i] ) - diamB;
		res += idx * D;
		res += S[idx];
		res += ( ( Q - idx ) * ( diamA[i] + 1 ) );
	}
	printf("%.3f\n", (double)res/(Q*N) );
}

int main(){	
	while ( scanf("%d %d", &N, &Q) == 2 ){
		process();
		for ( int i=0; i < N; ++i ) A[i].clear();
		for ( int i=0; i < Q; ++i ) B[i].clear();
	}
	return 0;
}
