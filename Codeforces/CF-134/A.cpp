#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 128;
int X[MAXN];
int Y[MAXN];
int p[MAXN];
int C[MAXN];

inline int find_set( const int &x ){
	return ( x == p[x] )? x:( p[x] = find_set(p[x]) );
}

int main(){
	int N;
	int u, v;
	scanf("%d", &N);
	
	for ( int i=0; i < N; ++i ){
		scanf("%d %d", X + i, Y + i);
		p[i] = i;
	}
	
	// Make the trivial connections
	for ( int i=0; i < N; ++i )
		for (int j=i+1; j < N; ++j ){
			if (X[i] == X[j] || Y[i] == Y[j]){
				u = find_set(i);
				v = find_set(j);
				if ( u != v ){
					p[v] = u;
				}
			}
		}


	
	for ( int i=0; i < N; ++i )
		C[i] = find_set(i);
	sort(C, C + N);
	int ncmp = unique(C, C + N) - C;
	printf("%d\n", ncmp - 1);
	return 0;
}
