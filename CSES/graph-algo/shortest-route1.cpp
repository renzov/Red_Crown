#include<cstdio>
#include<climits>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN = 100005;
typedef pair<long long, int> node;

int N, M;
vector<int> G[MAXN];
vector<int> W[MAXN];
long long d[MAXN];

void dijkstra(){
	fill( d, d + N, LLONG_MAX );
	priority_queue< node, vector<node>, greater<node> > q;

	d[0] = 0;
	q.push( node(0LL, 0) );
	
	int u, v;
	long long w;
	while ( !q.empty() ){
		w = q.top().first;
		u = q.top().second;
		q.pop();
		
		if ( w > d[u] ) continue;
		for ( int i=0; i < (int)G[u].size(); ++i ){
			v = G[u][i];
			if ( w + W[u][i] < d[v] ){
				d[v] = w + W[u][i];
				q.push( node( d[v], v ) );
			}
		}
	}
}

int main(){
	scanf("%d %d", &N, &M);
	
	int u, v, w;
	while ( M-- ){
		scanf("%d %d %d", &u, &v, &w);
		u--, v--;
		G[u].push_back(v);
		W[u].push_back(w);
	}
	dijkstra();
	printf("%lld", d[0]);
	for ( int i=1; i < N; ++i )
		printf(" %lld", d[i]);
	puts("");
	return 0;
}
