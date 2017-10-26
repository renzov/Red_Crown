#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

const int MAXN = 100005;
const int LOG = 19;
int N;
vector<int> G[MAXN];
int indeg[MAXN] = {0};
int nxt[MAXN];
int comp[MAXN];
int ord[MAXN] = {0};
int d[MAXN];
int inCycle[MAXN];
int pos[MAXN];
int size[MAXN];
int P[MAXN][LOG];
int num;
int vert;

void dfs( int u, int par ,int depth ){
	comp[ u ] = num;
	inCycle[u] = vert;
	d[ ord[u] ] = depth + 1;
	P[ ord[u] ][ 0 ] = par;
	for ( int i=0; i < (int)G[u].size(); ++i )
		dfs( G[u][i], ord[u], depth + 1 );
}

void mark( int u ){
	vert = u;
	d[ ord[u] ] = 0;
	P[ ord[u] ][0] = 0;
	for ( int i=0; i < (int)G[u].size(); ++i ){
		if ( ord[ G[u][i] ] > 0 && ord[ G[u][i] ] < num ) dfs( G[u][i], ord[u], 0 );
	}
}

int lca( int u, int v ){
	if ( d[u] < d[v] ) swap(u, v);
	int log;
	for ( log=1; (1<<log) <= d[u]; ++log);
	log--;
	for ( int i=log; i >= 0; --i )
		if ( (d[u] - d[v]) >= (1<<i) )
			u = P[u][i];
	if ( u == v ) return u;

	for ( int i=log; i >= 0; --i ){
		if ( P[u][i] != 0 && P[u][i] != P[v][i] )
			u = P[u][i], v = P[v][i];
	}
	return P[u][0];
}

int main(){
	int u, v;

	while ( scanf("%d", &N) != EOF ){
		for ( int i=1; i <= N; ++i ){
			scanf("%d", nxt + i );
			indeg[ nxt[i] ]++;
			G[ nxt[i] ].push_back(i); // reverse arc
		}
		// Do a topological numbering
		queue<int> q;
		for ( int i=1; i <= N; i++ )
			if ( indeg[i] == 0 ) q.push( i );
		
		num = 1;		
		while ( !q.empty() ){
			u = q.front();
			ord[u] = num++;
			q.pop();
			v = nxt[u];
			indeg[v]--;
			if ( indeg[v] == 0 ) q.push( v );
		}
		// Now, number every element in a cycle with the same 
		// number
		for ( int i=1; i <= N; ++i ){
			if ( ord[i] == 0 ){ //vertex in a cycle
				u = i;
				inCycle[u] = u;
				ord[u] = num;
				comp[u] = num;
				pos[u] = 0;
				size[num] = 1;				
				mark( u );
				v = nxt[u];					
				while ( v != u ){
					ord[v] = num;
					comp[v] = num;
					inCycle[v] = v;
 					mark( v );					
					pos[ v ] = size[num]++;					
					v = nxt[v];
				}
				num++;
			}
		}
		// Precomputation for LCA 
		for ( int j=1; (1 << j) < num; ++j )
			for ( int i=1; i <= num; ++i )
				P[i][j] = 0;

		for ( int j=1; (1 << j) < num; ++j )
			for ( int i=1; i <= num; ++i )
				if ( P[i][j-1] != 0 )
					P[i][j] = P[ P[i][j-1] ][j-1];

		int Q;
		int w, res;
		scanf("%d", &Q);
		while ( Q-- ){
			scanf("%d %d", &u, &v);
			if ( comp[u] != comp[v] ){ 
				puts("-1"); 
				continue;
			}
			if ( ord[u] == ord[v] ){ // In a cycle
				if ( pos[u] > pos[v] ) swap(u, v);
				printf("%d\n", min( pos[v] - pos[u], size[ord[u]] + pos[u] - pos[v] ));
			}
			else {
				w = lca( ord[u], ord[v] );
				if ( w == comp[u] ){ // path pass though the root
					res = d[ ord[u] ] + d[ ord[v] ] - 2*d[w];
					u = inCycle[u];
					v = inCycle[v];
					if ( pos[u] > pos[v] ) swap(u, v);
					res += min( pos[v] - pos[u], size[ord[u]] + pos[u] - pos[v] );
					printf("%d\n", res);
				}
				else {
					printf("%d\n", d[ ord[u] ] + d[ ord[v] ] - 2*d[w]);
				}
			}
		}		
		// Prepare for next testcase
		for ( int i=1; i <= N; ++i ){
			G[i].clear();
			ord[i] = size[i] = indeg[i] = 0;
		}
	}
	return 0;
}

