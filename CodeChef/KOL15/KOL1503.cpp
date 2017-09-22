#include<cstdio>
#include<set>
#include<map>
#include<vector>
#include<climits>
using namespace std;
typedef pair<int,int> pii;
const int MAXN = 100005;
const int LOG = 19;
vector<int> T[MAXN];
int N, Q;
char par[MAXN];
int P[MAXN][LOG];
int d[MAXN];
int pref[MAXN];
int suff[MAXN];
int f[MAXN] = {0};
map<int,int> S;

void dfs( int u, int p ){
	f[u] = f[p] + ( par[u] == '('? 1:-1 );
	d[u] = d[p] + 1;
	//printf("Vertex %d: f = %d - d = %d\n", u, f[u], d[u]);
	P[u][0] = p;	
	int v;
	// Calculate value of pref and suff
	if ( par[u] == '(' ){
		//puts("No suffix");
		suff[u] = 0;
		if ( S.count( f[u] + 1 ) == 0 ){
			pref[u] = d[u] + 1;
			//printf("Not found f + 1, pref = %d\n", pref[u]);			
		}
		else {
			pref[u] = d[u] - S[ f[u] + 1 ] - 1;
			//printf("Found at depth %d - pref = %d\n", it->second, pref[u]);
		}
	}
	else {
		//puts("No prefix");
		pref[u] = 0;
		if ( S.count( f[u] - 1 ) == 0 ){
			suff[u] = d[u] + 1;	
			//printf("Not found f - 1, suff = %d\n", suff[u]);
		}
		else {
			suff[u] = d[u] - S[ f[u] - 1 ] - 1;
			//printf("Found at depth %d - suff = %d\n", it->second, suff[u]);
		}
	}
	// Insert pair ( f, depth )
	bool elim = S.count( f[u] ) == 0;
	int last = S[ f[u] ];
	S[ f[u] ] = d[u];
	for ( int i=0; i < (int) T[u].size(); ++i ){
		v = T[u][i];
		if ( v != p )	dfs( v , u );
	}
	// delete pair ( f, depth )
	if ( elim ) S.erase( f[u] );
	else S[ f[u] ] = last;
}

void precalc(){
	for ( int i=1; i <= N; ++i )
		for ( int j=1; (1<<j) <= N; ++j )
			P[i][j] = 0;

	for ( int j=1; (1<<j) <= N; ++j )
		for ( int i=1; i <= N; ++i )
			if ( P[i][j-1] > 0 )
				P[i][j] = P[ P[i][j-1] ][ j - 1 ];
}

int lca( int p, int q ){
	if ( d[p] < d[q] ) swap(p, q);
	int log;	
	for ( log = 1; (1 << log) <= d[p]; ++log );
	log--;
	// Find the ancestor of p in the same level as q
	for ( int i=log; i >= 0; --i )
		if ( (d[p] - (1<<i)) >= d[q] )
			p = P[p][i];

	if ( p == q ) return p;

	for ( int i=log; i >= 0; --i )
		if (P[p][i] > 0 && P[p][i] != P[q][i] )
			p = P[p][i], q = P[q][i];

	return P[p][0];
}

int main(){
	int runs;
	int u, v, w;
	
	d[0] = -1;
	S[0] = -1;
	scanf("%d", &runs);	
	while ( runs-- ){
		scanf("%d %d", &N, &Q);
		for ( int i=1; i < N; ++i ){
			scanf("%d %d", &u, &v);
			T[u].push_back(v), T[v].push_back(u);
		}
		for ( int i=1; i <= N; ++i ) scanf(" %c", &par[i]);
		// Calculate depth, f, pref, suff
		dfs(1, 0);	
		// For LCA computation		
		precalc();
		int p;
		//	Answer the queries
		while ( Q-- ){
			scanf("%d %d", &u, &v);
			if ( u == v ){
				puts("No");
				continue;
			}
			w = lca( u , v );
			//printf("LCA(%d, %d) = %d\n", u, v, w);
			p = P[w][0];	
			if ( w == v ){
				if ( pref[u] >= d[u] - d[p] && f[u] - f[p] == 0 ){
					puts("Yes");
				}
				else {
					puts("No");
				}				
			}
			else if ( w == u ){
				if ( suff[v] >= d[v] - d[p] && f[v] - f[p] == 0 ){
					puts("Yes");
				}
				else {
					puts("No");
				}
			}
			else {
				bool ok = pref[u] >= d[u] - d[p];
				ok &= suff[v] >= d[v] - d[w];
				ok &= f[u] - f[p] == f[w] - f[v]; 
				puts(ok? "Yes":"No");
			}
		}
		
		if ( runs ){ // Clean up memory
			for ( int i=1; i <= N; ++i )
				T[i].clear();
			S.clear();
			S[0] = -1; // The parent of the root 	
		}
	}
	return 0;
}
