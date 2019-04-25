#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 128;
bool know[MAXN][MAXN];
int p[MAXN];
int ncmp;
int frec[MAXN];

inline int find_set(const int &x){
	return (x == p[x])? x:(p[x] = find_set(p[x]));
}

void union_set( int u, int v ){
	u = find_set(u);
	v = find_set(v);
	if ( u != v ){
		p[v] = u;
		ncmp--;
	}
}

int main(){
	
	int N, M;
	int K, x;
	int trivial = 0;
	scanf("%d %d", &N, &M);
	
	for ( int i=0; i < N; ++i ){
		p[i] = i;
		scanf("%d", &K);
		if ( K == 0 ) trivial++;
		while ( K-- ){
			scanf("%d", &x);
			x--;
			know[i][x] = true;
		}
	}
	
	ncmp = N;
	int u;
	for ( int i=0; i < M; ++i ){
		u = -1;	
		for ( int v=0; v < N; ++v )
			if ( know[v][i] ){
				if ( u >= 0 ){
					union_set( u , v );
				}
				u = v; 
			}
	}
	if ( trivial == ncmp )
		printf("%d\n", ncmp);
	else 
		printf("%d\n", ncmp - 1);
	return 0;
}
