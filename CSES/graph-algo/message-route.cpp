#include<cstdio>
#include<climits>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN = 100005;
int N, M;

vector<int> G[MAXN];
int pre[MAXN];
int d[MAXN];

void print_path( const int &v ){
	if ( pre[v] != -1 )
		print_path( pre[v] );
	
	if ( pre[v] != -1 ) putchar(' ');
	printf("%d", v + 1);
} 

void bfs( const int &s, const int &t ){
	fill( pre, pre + N, -1 );	
	fill( d, d + N, INT_MAX );
	queue<int> q;

	d[s] = 0;
	q.push( s );

	int u, v;
	while ( !q.empty() ){
		u = q.front();
		q.pop();
		
		if ( u == t ) break;

		for ( int i=0; i < (int)G[u].size(); ++i ){
			v = G[u][i];
			if ( d[v] == INT_MAX ){
				q.push( v );
				d[v] = d[u] + 1;
				pre[v] = u;
			}
		}
	}
	
	if ( d[t] == INT_MAX ){
		puts("IMPOSSIBLE");
	}
	else {
		printf("%d\n", d[t] + 1);
		print_path( t );
		puts("");
	}
}

int main(){
	scanf("%d %d", &N, &M);

	int u, v;
	while ( M-- ){
		scanf("%d %d", &u, &v);
		u--, v--;
		G[u].push_back( v );
		G[v].push_back( u );
	}
	bfs( 0, N - 1 );
	return 0;
}
