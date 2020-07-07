#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN = 100005;

int fact[1000005];
int A[MAXN];
vector<int> prime[MAXN];
vector<int> expo[MAXN];
int N;
int Q;

int log;
int L[MAXN];
int dfsnum;
int st[MAXN];
int ed[MAXN];
vector<int> T[MAXN];
int dfsord[2*MAXN];

void clean(){
	for ( int i=0; i < N; ++i ){
		prime[i].clear(); 
		expo[i].clear();
		T[i].clear();
	}
}

void dfs( const int &u, const int &p ){
	st[ u ] = dfsnum;
	dfsord[ dfsnum++ ] = u;
	int v;
	for ( int i=0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		if ( v == p ) continue;
		L[v] = L[u] + 1, P[0][v] = u;
		dfs( v, u );
	}
	ed[ u ] = dfsnum;
	dfsord[ dfsnum++ ] = u;
}

void factorize( const int &idx ){
	int x = A[idx];
	int y;
	while ( x > 1 ){
		if ( !fact[x] ){
			prime[idx].push_back( x ), expo[idx].push_back( 1 );
			x = 1;
		}
		else {
			y = fact[x];
			e = 0;
			while ( y == fact[x] ){
				e++, x /= y;	
			}
			prime[idx].push_back( y ), expo[idx].push_back( e );
		}
	}
}

void preprocess(){
	for ( int i=4; i <= 1000000; i+= 2 )
		fact[i] = 2;
	for ( int i=3; i*i < 1000000; i += 2 ){
		if ( !fact[i] ){
			for ( int j=i*i; j < 1000000; j += (i << 1) )
				fact[j] = i;
		}
	}
}

void process(){
	int u, v, w;

	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d", A + i );
		factorize(i);	
	}
	for ( int i=1; i < N; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		T[u].push_back(v), T[v].push_back(u);
	}
	// find dfs numbering
	dfsnum = 0;
	L[0] = 0, P[0][0] = -1; 
	dfs( 0, -1 );
	// LCA precomputation
	for ( log = 0; (1 << log) <= N; ++log );
	log--;
	for ( int i=1; i <= log; ++i ){
		fill( P[i], P[i] + N, -1 );
		for ( int j=0; j < N; ++j ){
			if ( P[i - 1][j] != -1 )
				P[i][j] = P[ i - 1 ][ P[i - 1][j] ];
		}	
	}
	scanf("%d", &Q);
	for ( int i=0; i < Q; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		if ( L[u] > L[v] ) swap( u, v );
		w = lca(u, v);
		if ( u == v ){
		
		}
		else {
		
		}
	}
	sort( q, q + N );
	// Mo
	for ( int i=0; i < Q; ++i ){
	
	}
	//print the answers
	for ( int i=0; i < Q; ++i )
		printf("%d\n", res[i]);
	clean();
}



int main(){
	preprocess();

	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}
