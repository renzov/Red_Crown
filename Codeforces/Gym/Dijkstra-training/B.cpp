#include<cstdio>
#include<climits>
#include<vector>
#include<queue>
using namespace std;

typedef pair<long long, int> node;
const int MAXN = 70005;

vector<int> G[MAXN];
vector<int> W[MAXN];
long long d[MAXN];
int p[MAXN];

void print_path( const int &u ){
	if ( p[u] == -1 ){
		printf("%d", u + 1 );
		return; 
	}
	print_path( p[u] );
	printf(" %d", u + 1);
}

void dijkstra( const int &s, const int &t, const int &N ){
	fill( d, d + N, LLONG_MAX );
	d[s] = 0;
	p[s] = -1;
	
	priority_queue< node, vector<node>, greater<node> > Q;
	Q.push( node( 0, s ) );

	int u, v, w;
	long long Du;

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
				p[v] = u;
				Q.push( node( d[v], v ) );
			}
		}
	}
}

int main(){
	int N, M, s, t;
	int u, v, w;
	
	freopen("distance.in", "r", stdin);
	freopen("distance.out", "w", stdout);

	scanf("%d %d %d %d", &N, &M, &s, &t);
	s--, t--;
	
	while ( M-- ){
		scanf("%d %d %d", &u, &v, &w );
		u--, v--;
		G[u].push_back(v), W[u].push_back(w);
		G[v].push_back(u), W[v].push_back(w);
	}
	
	dijkstra( s, t, N );
	if ( d[t] == LLONG_MAX )
		puts("-1");
	else {
		printf("%lld\n", d[t]);
		print_path( t );
		puts("");
	}
	return 0;
}
