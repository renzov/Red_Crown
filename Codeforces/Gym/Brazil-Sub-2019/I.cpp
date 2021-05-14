#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 420;

int T[MAXN];
int T2[MAXN];
int ord[MAXN];
int rev[MAXN];
int W[MAXN][MAXN][MAXN];
int R[MAXN][MAXN][MAXN];


bool cmp( const int &i, const int &j ){
	return T[i] < T[j];
}

void floyd( int C[MAXN][MAXN][MAXN], int *order, const int &N ){
	int k;
	for ( int idx = 1; idx <= N; ++idx ){
		k = order[idx];
		for ( int i=1; i <= N; ++i )
			for ( int j=1; j <= N; ++j )
				C[idx][i][j] = min( C[idx][i][j] , C[idx - 1][i][k] + C[idx - 1][k][j] );
	}
}

int main(){

	int N, M;

	scanf("%d %d", &N, &M);
	for ( int i=1; i <= N; ++i ){
		scanf("%d", T + i);
		T2[i] = T[i];
		ord[i] = i;
	}
	
	sort( ord + 1, ord + (N + 1), cmp );
	for ( int i=1; i <= N; ++i ){
		rev[i] = ord[N - i + 1];
	}

	sort( T2 + 1, T2 + (N + 1) );
	int S = unique( T2 + 1, T2 + (N + 1) ) - T2;
	S--;

	int u, v, w;
	
	while ( M-- ){
		scanf("%d %d %d", &u, &v, &w);
		W[0][u][v] = W[0][v][u] = w;
		R[0][u][v] = R[0][v][u] = w;
	}
	
	floyd( W, ord, N );
	floyd( R, rev, N );

	int Q, k, t;
	scanf("%d", &Q);
	/*
	while ( Q-- ){
		scanf("%d %d %d %d", &u, &v, &k, &t);
		u--, v--;
		if ( k > S ) k = S;
		if ( t ){

		}
		else {

		}
	}
	*/
	return 0;
}
