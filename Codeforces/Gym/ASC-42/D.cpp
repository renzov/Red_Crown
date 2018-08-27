#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <vector>

using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

const int MAXN = 100005;
const int MLOG = 19;
int N;
int log;
int root;
vector<int> T[MAXN];
int L[MAXN];
int P[MLOG][MAXN];

void clean_up(){
	for ( int i=0; i < N; ++i )
		T[i].clear();
}

void dfs( const int &u, const int &p ){
	int v;
	for ( int i=0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		if ( v == p ) continue;
		L[v] = L[u] + 1;		
		dfs( v, u );
		P[0][v] = u;
	}
}

int go_up( int u, int D ){
	for ( int i=log; D >= 0 && i >= 0; --i ){
		if ( D >= (1<<i) ){
			D -= (1<<i);
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
	root = 0;
	L[root] = 0;
	int u , v; 

	for ( log=0; (1<<log) < N; ++log );
	log--;
	log = max(log , 0);

	for ( int i=1; i < N; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		T[u].push_back(v);
		T[v].push_back(u);
	}
	for ( int i=0; i <= log; ++i )
		fill( P[i], P[i] + N, -1 );
	dfs( 0 , -1 );
	for ( int i=1; i <= log; ++i )
		for ( int j=0; j < N; ++j )
			if ( P[i-1][j] != -1 )
				P[i][j] = P[ i - 1 ][ P[i-1][j] ];
	int Q;
	char op;
	int a, b;
	scanf("%d", &Q);
	while ( Q-- ){
		scanf(" %c", &op);
		if ( op == '?' ){
			scanf("%d %d", &u, &v);
			u--, v--;
			if ( root == 0 ) printf("%d\n", lca( u, v ) + 1 );
			else {
				a = lca( root, u );		
				b = lca( root, v );
				if ( a == b ){
					printf("%d\n", lca(u, v) + 1 );
				}
				else if ( L[a] < L[b] ){
					printf("%d\n", b + 1);
				}
				else {
					printf("%d\n", a + 1);
				}
			}
		}
		else {
			scanf("%d", &root);
			root--;
		}
	}
}

int main(){
	freopen ("dynamic.in", "r", stdin);
	freopen ("dynamic.out", "w", stdout);
	while ( scanf("%d", &N) && N > 0 ){
		process();
		clean_up();
	}
	return 0;
}

