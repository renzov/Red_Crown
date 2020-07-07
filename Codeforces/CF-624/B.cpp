#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 128;
int A[MAXN];
int f[MAXN];
int maxi[MAXN];
int mini[MAXN];

int find_set(const int &x){ return x == f[x]? x:( f[x] = find_set( f[x] ) ); }
void link( int u, int v ){
	if ( u == v ) return;
	maxi[v] = max( maxi[v], maxi[u] );
	mini[v] = min( mini[v], mini[u] );
	f[u] = v;
}
void process(){
	int N, M;
	scanf("%d %d", &N, &M);
	for ( int i=1; i <= N; ++i ){
		scanf("%d", A + i);
		f[i] = i, maxi[i] = A[i], mini[i] = A[i];	
	}
	int u, v;
	while ( M-- ){
		scanf("%d", &u);
		link( find_set(u), find_set(u + 1) );
	}
	bool ok = true;
	for ( int i=1; ok && i < N; ++i ){
		u = find_set(i), v = find_set(i + 1);
		if ( u != v ) 
			ok &= ( maxi[u] <= mini[v] );
	}
	puts(ok? "YES":"NO");
}

int main(){

	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();

	return 0;
}
