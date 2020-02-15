#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
#include<climits>
using namespace std;
const int MAXN = 10005;
typedef pair<int,int> pii;
int N, M;
vector<int> G[MAXN];
vector<int> W[MAXN];
int ds[MAXN];
int dt[MAXN];

void dijkstra( const int &s, const int &t, int d[] ){
	fill( d, d + N, INT_MAX );
	priority_queue< pii, vector<pii>, greater<pii> > q;
	d[s] = 0;
	q.push( pii(0, s) );
	
	int u, v, du, w;
	while ( !q.empty() ){
		u = q.top().second;
		du = q.top().first;
		q.pop();
		if ( du > d[u] ) continue;
		for ( int i=0; i < (int)G[u].size(); ++i ){
			v = G[u][i];
			w = W[u][i];
			if ( d[v] > du + w ){
				d[v] = du + w;
				q.push( pii( d[v], v ) );
			}
		}
	}
}


void process(){
	int u, v, w;
	for (int i=0; i < M; ++i){
		scanf("%d %d %d", &u, &v, &w);
		if ( u == v ) continue;
		G[u].push_back(v), G[v].push_back(u);
		W[u].push_back(w), W[v].push_back(w);
	}
	dijkstra( 0, N-1, ds );
	dijkstra( N-1, 0, dt );
	int dmin = ds[N-1];
	long long res = 0;
	for ( u=0; u < N; ++u ){
		for ( int i=0; i <(int)G[u].size(); ++i ){
			v = G[u][i];
			w = W[u][i];
			if ( u > v ) continue;	// only process pairs (u,v) where u < v
			if ( (ds[u] + dt[v] + w == dmin) || 
				 (ds[v] + dt[u] + w == dmin) )
				 	res += w;
		}
	}
	printf("%lld\n", res << 1);
	// Clean memory
	for ( int i=0; i < N; ++i )
		G[i].clear(), W[i].clear();
}

int main(){
	while ( scanf("%d %d", &N, &M) == 2 ) process();  
	return 0;
}
