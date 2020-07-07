#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef pair<int,int> edge;
const int MAXN = 1000005;
const int MAXM = 2*MAXN;

edge E[MAXM];
int res[MAXM];
int f[MAXN];

int p[MAXN];
int L[MAXN];
vector<int> T[MAXN];
int N, M;

inline int find_set( const int &x ){ return x == f[x]? x:( f[x] = find_set(f[x]) ); }

void dfs( const int &u, const int &par ){
	int v;
	for ( int i=0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		if ( v == par ) continue;
		L[v] = L[u] + 1;
		p[v] = u;
		dfs( v, u );
	}
}

int main(){
	int u, v, par;
	scanf("%d %d", &N, &M);
	for ( int i=0; i < N; ++i ){ 
		f[i] = i;
		p[i] = -1;
		L[i] = -1;
	}
	// Read the graph data
	for ( int i=0; i < M; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		E[i] = edge( u, v );
		if ( u == v ){	// loop
			res[i] = 1;
		}
		else if ( find_set(u) != find_set(v) ){	// tree edge
			f[find_set(u)] = find_set(v);
			T[u].push_back(v), T[v].push_back(u);
			res[i] = 0;
		}
		else {	// nontree edge
			res[i] = -1;
		}
	}
	// root each tree in the forest
	for ( int i=0; i < N; ++i )
		if ( L[i] == -1 ){
			L[i] = 0;
			dfs( i, -1 );
		}
	// Reinitialize for the next step	
	for ( int i=0; i < N; ++i ) f[i] = i;
	// find the response for the next queries
	for ( int i=0; i < M; ++i ){
		if ( res[i] != -1 ) continue;
		// Observation since res[i] == -1, the edge uv, 
		// link two vertices in the same component considering edges 1 ... i - 1
		u = E[i].first, v = E[i].second;
		u = find_set(u), v = find_set(v);
		res[i] = 1;
		while ( u != v ){
			if ( L[v] >= L[u] ){
				res[i]++;
				par = find_set( p[v] );
				f[v] = par;
				v = par;
			}
			if ( L[u] >= L[v] ){
				res[i]++;
				par = find_set( p[u] );
				f[u] = par;
				u = par;
			}
		}
	}
	for ( int i=0; i < M; ++i )
		printf("%d\n", res[i]);
	return 0;
}
