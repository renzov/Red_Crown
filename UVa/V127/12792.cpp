#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN = 200005;

bool visited[MAXN];
int f[MAXN];

int dfs( const int &u ){
	if ( visited[u] ) return 0;
	visited[u] = true;
	return 1 + dfs( f[u] );
}

void process( const int &N ){	
	for ( int i = 0; i < N; ++i ){
		f[i] = (i << 1) + 1;
		f[i + N] = i << 1;	
	}

	fill( visited, visited + 2*N, false );
	vector<long long> ans;
	for ( int i = 0; i < 2*N; ++i ){
		if ( !visited[i] )
			ans.push_back( (long long)dfs( i ) );
	}

	long long g;
	long long lcm = ans[0];
	for ( int i = 1; i < ans.size(); ++i ){
		g = __gcd( lcm, ans[i] );
		lcm *= ans[i];
		lcm /= g;
	}
	printf("%lld\n", lcm);
}

int main(){
	int N;
	while ( scanf("%d", &N) == 1 )
		process( N >> 1 );
	return 0;
}
