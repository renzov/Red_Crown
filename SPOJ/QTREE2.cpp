#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
const int MLOG = 18;
const int MAXN = 10005;
vector<int> T[MAXN];
vector<int> W[MAXN];
int N;
int log;
int P[MLOG][MAXN];
int d[MAXN];
int L[MAXN];

void clean_up(){
	for ( int i=0; i < N; ++i ){
		T[i].clear();
		W[i].clear();
	}
}

void dfs( const int &u, const int &p ){
	int v, w;
	for ( int i=0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		w = W[u][i];
		if ( v == p ) continue;
		P[0][v] = u;
		d[v] = d[u] + w;
		L[v] = L[u] + 1;
		dfs( v, u );
 	}
}

int go_up( int u, int D ){
	for ( int i=log; D >= 0 && i >= 0; --i ){
		if ( (1 << i) <= D ){
			D -= ( 1 << i );
			u = P[i][u];
		}
	}
	return u;
}

int lca( int u, int v ){
	if ( L[u] > L[v] ) swap(u, v);
	v = go_up( v, L[v] - L[u] );
	if ( u == v ) return u;
	for ( int i=log; i >= 0; --i )
		if ( P[i][u] != -1 && P[i][u] != P[i][v] )
			u = P[i][u], v = P[i][v];
	return P[0][u];
}

void process(){
	int u, v, w, l, k;
	char op[10];
	
	scanf("%d", &N);
	for ( int i=1; i < N; ++i ){
		scanf("%d %d %d", &u, &v, &w);
		u--, v--;
		T[u].push_back(v); W[u].push_back(w);
		T[v].push_back(u); W[v].push_back(w);
	}

	for ( log = 0; (1<<log) < N; ++log );
	log--;
	
	for ( int i=0; i <= log; ++i )
		fill( P[i] , P[i] + N, -1 );
	
	L[0] = d[0] = 0; 
	dfs( 0, -1 );
	for ( int i=1; i <= log; ++i )
		for ( int j=0; j < N; ++j )
			if ( P[i-1][j] != -1 )
				P[ i ][ j ] = P[ i - 1 ][ P[ i - 1 ][ j ] ];	

	while ( 1 ){
		scanf("%s", op);
		if ( op[1] == 'O' ) break;
		scanf("%d %d", &u, &v);
		u--, v--;
		l = lca( u , v );
		if ( op[1] == 'I' ){ // Dist
			printf("%d\n", d[u] - d[l] + d[v] - d[l]);
		}
		else { // Kth
			scanf("%d", &k);
			k--;
			if ( k <= (L[u] - L[l]) ){
				printf("%d\n", go_up(u, k) + 1);
			}
			else {
				k -= ( L[u] - L[l] );
				printf("%d\n", go_up( v , L[v] - L[l] - k ) + 1);
			}
		}
	}
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- ){
		process();
		puts("");
		clean_up();
	}
	return 0;
}
