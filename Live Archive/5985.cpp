#include <cstdio>
#include <algorithm>
#include <vector>

#define repn( i , a , b ) for( int i = ( int ) a ; i < ( int ) b ; i ++ )
#define rep( i , n ) repn( i , 0 , n ) 
#define all( x )  x.begin() , x.end()
#define rall( x ) x.rbegin() , x.rend()
#define mp make_pair
#define fst first
#define snd second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

const int MAXM = 55;
const int MAXSUB = 1 << 13;
int V[MAXM];
int size[MAXM];
int X[MAXM][MAXM];
int S1[MAXM][MAXSUB];
int S2[MAXM][MAXSUB];
int L1[MAXM];
int L2[MAXM];
int ord[MAXM];
vector< int > G[MAXM];
int match[MAXM];
int seen[MAXM];
int ti;

void generate_subsets( int *A, int m, int *S, int &tam){
	// A is the array of m values
	// S is the array we will generate
	if ( m == 0 ){
		S[0] = 0;
		tam = 1;
		return;
	}
	tam = 0;
	int val;
	for ( int i=0; i < (1<<m); ++i ){
		val = 0;
		for ( int j=0; j < m; ++j )
			if ( (i >> j) & 1 ) val += A[j];
		S[tam++] = val;
	}
	sort( S, S + tam );
	tam = unique( S, S + tam ) - S;
}

bool exist( int v, int *A, int *B, int n, int m ){
	// Given v and to sorted lists A and B, return if exist A[i] + B[j] = v
	int i = 0;
	int j = m-1;
	while ( i < n && j >= 0 && A[i] <= v ){
		while ( j >= 0 && A[i] + B[j] > v )
			j--;
		if ( j >= 0 && (A[i] + B[j] == v) ) return true;
		i++;
	}
	return false;
}

bool cmp( const int &a, const int &b ){
	return V[a] < V[b];
}

bool alt_path( int u ){
	if ( seen[u] >= ti ) return false;
	seen[u] = ti;
	int v;
	for ( int i=0; i < G[u].size(); ++i ){
		v = G[u][i];
		if ( match[v] == -1 || alt_path( match[v] ) ){
			match[v] = u;
			return true;
		}
	}
	return false;
}

int main(){
	int runs;
	int N,M;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d", &M, &N);
		for ( int i=0; i < M; ++i ) scanf("%d", V+i);
		for ( int i=0; i < N; ++i ){
			scanf("%d", size + i);
			for ( int j=0; j < size[i]; ++j ) scanf("%d", &X[i][j]);
		}	
		// prepare for meet in the middle
		int mid;
		for ( int i=0; i < N; ++i ){
			mid = size[i] >> 1;
			generate_subsets( X[i] , mid, S1[i], L1[i] );
			generate_subsets( X[i] + mid, size[i] - mid, S2[i], L2[i] );
		}
		// create the graph
		for ( int i=0; i < M; ++i ) G[i].clear();
		for ( int i=0; i < M; ++i ){
			for ( int j=0; j < N; ++j )
				if ( exist( V[i] , S1[j], S2[j], L1[j], L2[j] ) )
					G[i].push_back(j);
		}
		// sort the vertices by indices
		for ( int i=0; i<M; ++i ) ord[i] = i;
		sort( ord, ord + M, cmp );
		int res = 0;
		// find the matchable set of maximum weight
		fill( match, match + N, -1 );
		fill( seen, seen + M, -1 );
		ti = 0;
		for ( int i=M-1; i >= 0; --i ){
			if ( alt_path( ord[i] ) ) res += V[ ord[i] ];
			ti++;
		}
		printf("%d\n", res);
	}
	return 0;
}

