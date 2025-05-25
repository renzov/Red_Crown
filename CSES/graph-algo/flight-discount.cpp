#include<cstdio>
#include<climits>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

typedef pair<int, int> state;
typedef pair<long long, state> node;
const int MAXN = 200005;

int N, M;
vector<int> G[MAXN];
vector<int> W[MAXN];
long long d[2][MAXN];

void dijkstra(){
	fill( d[0], d[0] + N, LLONG_MAX );
	fill( d[1], d[1] + N, LLONG_MAX );

	priority_queue< node, vector<node>, greater<node> > q;
	q.push( node( 0, state(0, 0) ) );
	d[0][0] = 0;

	int u, v, t, nw;
	long long w;

	while ( !q.empty() ){
		w = q.top().first;
		u = q.top().second.first;
		t = q.top().second.second;
		q.pop();

		if ( w > d[t][u] ) continue;
		if ( u == (N - 1) ){
			printf("%lld\n", d[t][u]);
			break;
		}

		for ( int i=0; i < (int)G[u].size(); ++i ){
			v = G[u][i];
			nw = W[u][i];

			if ( nw + w < d[t][v] ){
				d[t][v] = w + nw;
				q.push( node( d[t][v] , state(v, t) ) );
			}
			nw >>= 1;
			if ( t == 0 ){
				if ( nw + w < d[1][v] ){
					d[1][v] = nw + w;
					q.push( node( d[1][v], state( v, 1 ) ) );
				}
			}
		}
	}	
}

int main(){
	int u, v, w;

	scanf("%d %d", &N, &M);
	while ( M-- ){
		scanf("%d %d %d", &u, &v, &w);
		u--, v--;
		G[u].push_back(v), W[u].push_back(w);
	}
	dijkstra();
	return 0;
}
