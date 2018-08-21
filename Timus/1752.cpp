#include<cstdio>
#include<vector>
using namespace std;
const int MAXN = 20005;
const int MLOG = 18;
int a,b; //vertices that determine a longest path in the tree
int N;
int log;
int d[MAXN];
int P[MLOG][MAXN];
vector<int> T[MAXN];


int dfs(const int &u, const int &p){
	int v;
	int w = u;
	int z;
	for ( int i=0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		if ( v == p ) continue;
		P[0][v] = u;
		d[v] = d[u] + 1;
		z = dfs( v, u );	
		if ( d[w] < d[z] ) w = z;
	}
	return w;
}

void find_diameter(){
	d[0] = 0; 
	a = dfs(0, -1);
	d[a] = 0;
	b = dfs(a, -1);
}

int go_up( int u, int D ){
	for ( int i=log; D > 0 && i >= 0; --i ){
		if ( (1<<i) <= D ){
			D -= (1<<i);
			u = P[i][u];
		}
	}
	return u;
}

int lca( int u, int v ){
	if ( u == v ) return u;
	if ( d[u] > d[v] ) swap(u, v);
	v = go_up( v, d[v] - d[u] );
	if ( u == v ) return u;
	for ( int i = log; i >= 0; --i ){
		if ( P[i][u] != -1 && P[i][u] != P[i][v] )
			u = P[i][u], v = P[i][v];
	}
	return P[0][u];
}

int main(){
	int N;
	int u, v, w;
	int D, Q;
	
	scanf("%d %d", &N, &Q);
	for ( int i=1; i < N; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		T[u].push_back(v);
		T[v].push_back(u);
	}
	
	for ( int i=1; (1 << i) < N; ++i )
		fill( P[i], P[i] + N, -1 );

	find_diameter();
	//printf("a = %d - b = %d\n", a, b);
	for ( log = 0; (1<<log) < N ; log++ );
	log--;
	// LCA Preprocessing
	for ( int i=1; (1 << i) < N; ++i ){
		for ( int j=0; j < N; ++j )
			if ( P[i-1][j] != -1 )
				P[i][j] = P[ i-1 ][ P[i-1][j] ];
	}
	int l, db;
	while ( Q-- ){
		scanf("%d %d", &u, &w);
		u--;
		//printf("Q = %d - %d\n", u, w);
		l = lca( u , b );
		db = d[b] + d[u] - 2*d[l];
		if ( d[u] >= db ){
			l = a, v = a;
		}
		else {
			v = b;
		}
		// from now on, longest vertex from u is v, and lca is l
		if ( d[u] + d[v] - 2*d[l] < w ){
			puts("0");
		}
		else {
			if ( d[u] - d[l] >= w ){
				printf("%d\n", go_up( u , w ) + 1);
			}
			else {
				w -= ( d[u] - d[l] );
				printf("%d\n", go_up( v , d[v] - d[l] - w ) + 1);
			}
		}	
	}
	return 0;
}
