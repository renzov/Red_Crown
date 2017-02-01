#include <cstdio>
#include <set>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

const int MAXN = 100005;

int N;
vector<int> G[MAXN];
vector<int> C[MAXN];

vector<int> GT[MAXN];
vector<int> CT[MAXN];

void dijkstra( int s, vector<int> G[], vector<int> C[], int d[] ){
	//init
	for (int i=0; i < N; ++i ){
		d[i] = INT_MAX;
	}

	priority_queue< pair<int,int>, vector< pair<int,int> >, greater< pair<int,int> > > q;

	d[s] = 0;
	q.push( make_pair( 0 , s ) );

	int u, v, w, t;
	
	while ( !q.empty() ){
		u = q.top().second;
		t = q.top().first;
		q.pop();
		if ( d[u] < t ) continue;
		for ( int i=0; i < G[u].size(); ++i ){
			v = G[u][i];
			w = t + C[u][i];
			if ( d[v] > w ){
				d[v] = w; 
				q.push( make_pair( w , v ) );
			}
		}
	}
}

int main(){
	int runs;
	int M,K;
	int u,v,w;
	int s,t;

	int ds[MAXN];
	int dt[MAXN];

	scanf("%d",&runs);
	while (runs--){
		scanf("%d %d %d %d %d", &N, &M, &K, &s, &t);
		s--,t--;
		
		if ( N > 100004 ) while (1);

		for ( int i=0; i < N; ++i ){
			G[i].clear(); GT[i].clear();
			C[i].clear(); CT[i].clear(); 
		}

		while (M--){
			scanf("%d %d %d", &u, &v, &w);
			u--,v--;
			if ( u < N && v < N && u >= 0 && v >= 0 ){
				G[u].push_back(v); GT[v].push_back(u);
				C[u].push_back(w); CT[v].push_back(w);
			}
		}
		dijkstra(s, G, C, ds);
		dijkstra(t, GT, CT, dt);
		int res = ds[t];
		for (int i=0; i < K; ++i){
			scanf("%d %d %d", &u, &v, &w);
			u--, v--;
			if ( u < N && v < N && u >= 0 && v >= 0 ){
				if ( ds[u] != INT_MAX && dt[v] != INT_MAX ){
					res = min( res , ds[u] + w + dt[v] );
				}
				if ( ds[v] != INT_MAX && dt[u] != INT_MAX ){
					res = min( res , ds[v] + w + dt[u] );
				}
			}
		}
		if (res == INT_MAX) puts("-1");
		else printf("%d\n",res);
	}
	return 0;
}


