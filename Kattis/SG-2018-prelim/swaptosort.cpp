#include<cstdio>
using namespace std;
const int MAXN = 1000005;
int p[MAXN];

inline int find_set( const int &x ){ return x == p[x]? x:( p[x] = find_set(p[x]) ); }

int main(){

	int N, K;
	scanf("%d %d", &N, &K);
	for ( int i=1; i <= N; ++i ) p[i] = i;
	
	int cnt = N;
	int u, v;

	while ( K-- && cnt > 1 ){
		scanf("%d %d", &u, &v);
		u = find_set(u), v = find_set(v);
		if ( u != v ) p[v] = u, cnt--;
	}
	
	bool ok = true;
	for ( int i=N, j=1; i > 0 && ok; --i, j++ ){
		ok &= find_set( i ) == find_set( j );
	}
	puts( ok? "Yes":"No" );
	return 0;
}
