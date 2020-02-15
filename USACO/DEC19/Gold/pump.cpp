#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<queue>
#include<climits>
using namespace std;
const int MAXN = 1024;
typedef pair<int,int> pii;
int N, M;
vector<int> G[MAXN];
vector<int> W[MAXN];
vector<int> F[MAXN];

int d[MAXN];
int V[MAXN];
int dijkstra( const int &lb ){
	fill( d, d + N, INT_MAX );
	d[0] = 0;
	
	priority_queue< pii, vector<pii>, greater<pii> > q;
	int u, v, w, f, du;
	
	q.push( pii( 0, 0 ) );
	while ( !q.empty() ){
		du = q.top().first;
		u = q.top().second;
		q.pop();
		if ( du > d[u] ) continue;
		if ( u == N - 1 ) return du;
		for ( int i=0; i < G[u].size(); ++i ){
			v = G[u][i], w = W[u][i], f = F[u][i];
			if ( f < lb ) continue;
			if ( du + w < d[v] ){
				d[v] = du + w;
				q.push( pii( d[v], v) );
			}
		}
	}
	return d[N - 1];
}

int main(){
	freopen ("pump.in", "r", stdin);
	freopen ("pump.out", "w", stdout);

	int u, v, w, f;

	scanf("%d %d", &N, &M);
	for ( int i=0; i < M; ++i ){
		scanf("%d %d %d %d", &u, &v, &w, &f);
		u--, v--;
		G[u].push_back( v ), G[v].push_back(u);
		W[u].push_back( w ), W[v].push_back(w);
		F[u].push_back( f ), F[v].push_back(f);
		V[i] = f;
	}

	sort( V, V + M );
	M = unique( V, V + M ) - V;
	
	int numbest, numres;
	int denbest, denres;
	bool first = true;
	for ( int i=0; i < M; ++i ){
		numres = V[i];
		denres = dijkstra( numres );
		if ( denres < INT_MAX ){
			if ( first || numres * denbest > numbest * denres ){
				numbest = numres, denbest = denres;
				first = false;
			}
		}
	}
	printf("%d\n", numbest*1000000/denbest );
	return 0;
}
