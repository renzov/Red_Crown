#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 100005;
int N, M;
int P[MAXN];
int f[MAXN];

int find_set( const int &x ){
	if ( f[x] == x ) return x;
	int p = find_set( f[x] ); 
	P[x] = min( P[x], P[ f[x] ] );
	f[x] = p;
	return p;
}

int main(){
	// Read
	scanf("%d %d", &N, &M);
	for ( int i=0; i < N; ++i ){
		scanf("%d", P + i ); 
		f[i] = i;
	}
	// Process
	int u, v;
	char op;
	while ( M-- ){
		scanf(" %c", &op);
		if ( op == '+' ){
			scanf("%d %d", &u, &v);
			u--, v--;
			f[v] = u;
		}
		else { 
			scanf("%d", &u);
			u--;
			find_set( u );
			printf("%d\n", P[u]);
		}
	}
	return 0;
}

