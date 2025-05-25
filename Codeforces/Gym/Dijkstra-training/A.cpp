#include<cstdio>
#include<climits>
#include<vector>
#include<queue>
using namespace std;

typedef pair<long long, int> node;
const int MAXN = 2005;

vector<int> G[MAXN];
vector<long long> W[MAXN];
long long d[MAXN];

void dijkstra( const int &s, const int &t, const int &N ){
	fill( d, d + N, LLONG_MAX );
	d[s] = 0;
	
	priority_queue< node, vector<node>, greater<node> > Q;
	Q.push( node( 0, s ) );

	int u, v;
	long long w, Du;

	while ( !Q.empty() ){
		Du = Q.top().first;
		u = Q.top().second;
		Q.pop();
		if ( Du > d[u] ) continue;
		for ( int i = 0; i < (int)G[u].size(); ++i ){
			v = G[u][i];
			w = W[u][i];
			if ( Du + w < d[v] ){
				d[v] = Du + w;
				Q.push( node( d[v], v ) );
			}
		}
	}
}

int main(){
	int N, M, s, t;
	int u, v;
	long long w;
	
	freopen("dijkstra.in", "r", stdin);
	freopen("dijkstra.out", "w", stdout);

	scanf("%d %d %d", &N, &s, &t);
	s--, t--;
	for ( u = 0; u < N; ++u )
		for ( v = 0; v < N; ++v ){
			scanf("%lld", &w );
			if ( w > 0 )
				G[u].push_back(v), W[u].push_back(w);
		}
	
	dijkstra( s, t, N );
	if ( d[t] == LLONG_MAX )
		puts("-1");
	else 
		printf("%lld\n", d[t]);
	return 0;
}
