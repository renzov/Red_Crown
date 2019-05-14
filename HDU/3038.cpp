#include<cstdio>
using namespace std;

const int MAXN = 200050;
int f[MAXN];
int d[MAXN];

int find_set( const int &x ){
	if ( x == f[x] ) return x;
	int px = f[x];
	f[x] = find_set( px );
	d[x] +=  d[px];
	return f[x];
}

int main(){
	int N, M;
	int res = 0;
	int a, b, s;
	int pa, pb;

	while ( scanf("%d %d", &N, &M) != EOF ) {
		res = 0;
		for ( int i=0; i <= N; ++i ) f[i] = i, d[i] = 0;
		while ( M-- ){
			scanf("%d %d %d", &a, &b, &s);
			pa = find_set( a - 1 );
			pb = find_set( b );
			if ( pa != pb ){
				f[pb] = pa;			
				d[pb] = s - d[b] + d[a-1];
			}
			else if ( d[b] - d[a-1] != s ){
				res++;
			}
		}
		printf("%d\n", res);
	}
	return 0;
}

