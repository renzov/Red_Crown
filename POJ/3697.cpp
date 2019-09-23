#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
typedef pair<int,int> pii;
const int MAXN = 10005;

int N, M;
vector<int> G[MAXN];
int deg[MAXN] = {0};
bool nconn[MAXN];
priority_queue< pii, vector<pii>, greater<pii> > q;

int main(){
	int u, v, d;
	int cases = 0;
	while ( scanf("%d %d", &N, &M) && N ){
		// Clear memory for next testcase 
		for ( int i=0; i < N; ++i ) G[i].clear();	
		// Read the complement graph
		while ( M-- ){
			scanf("%d %d", &u, &v);
			u--, v--;
			G[u].push_back(v), G[v].push_back(u);
		}
		// Initialize 
		for ( int i=0; i < N; ++i ){
			nconn[i] = false;
			deg[i] = 0;
		}

		int res = 1;	// Number of vertices connected to vertex 1 (including vertex 1)
		for ( int i=0; i < (int)G[0].size(); ++i ){
			// Mark the ones that are not connected directly to vertex 1
			u = G[0][i];
			nconn[ u ] = true;	
		}
	
		for ( u=1; u < N; ++u )
			if ( nconn[u] ) 	// Calculate the degree of u induced by the vertices connected to 1
				for ( int j=0; j < (int)G[u].size(); ++j ){
					v = G[u][j];
					if ( !nconn[v] ) deg[u]++;
				}
			else 
				res++;
	
		for ( int i=1; i < N; ++i ){
			if ( nconn[i] )
				q.push( pii( deg[i], i ) );
			
		}
		while ( !q.empty() ){
			u = q.top().second;
			d = q.top().first;
			q.pop();

			if ( d != deg[u] ) continue;
			if ( d >= res ) break;	// if the minimum degree >= number of vertices connected to 1, there 
									// are no other vertex that can be connected
			
			// In this case u is connected to 1, we update the
			// degree of the remaining not connected vertices
			nconn[u] = false;
			res++;

			for ( int i=0; i < (int)G[u].size(); ++i ){
				v = G[u][i];
				if ( nconn[v] ){
					deg[v]++;
					q.push( pii( deg[v], v ) );
				}
			}
		}
		printf("Case %d: %d\n", ++cases, res - 1 );
	}
	return 0;
}
