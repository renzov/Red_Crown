#include<cstdio>
#include<vector>
using namespace std;

const int MAXN = 100005;

int f[MAXN];

inline int find_set( const int &x ){ return f[x] == x? x:( f[x] = find_set( f[x] ) ); }

int main(){
	int N, M;

	freopen( "maxincycle.in", "r", stdin );
	freopen( "maxincycle.out", "w", stdout );

	scanf("%d %d", &N, &M);

	for ( int i = 0; i < N; ++i )
		f[i] = i;

	vector<int> res;
	int u, v;
	for ( int i = 1; i <= M; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		u = find_set( u );
		v = find_set( v );
		if ( u != v ){
			res.push_back( i );
			f[v] = u;
		}
	}
	printf("%d\n", (int)res.size());
	for ( int i = 0; i < (int)res.size(); ++i ){
		if ( i ) putchar(' ');
		printf("%d", res[i]);
	}
	puts("");
	return 0;
}
