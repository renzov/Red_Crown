#include<cstdio>
#include<set>
#include<vector>
#include<climits>
using namespace std;
typedef pair<int,int> pii;
const int MAXN = 100005;
const int LOG = 18;
vector<int> T[MAXN];
int N, Q;
char par[MAXN];
int P[MAXN][LOG];
int d[MAXN];
int pref[MAXN];
int suff[MAXN];
int f[MAXN] = {0};
set<pii> S;

void dfs( int u, int p ){
	f[u] = f[p] + ( par[u] == '('? 1:-1 );
	d[u] = d[p] + 1;	
	P[u][0] = p;	
	int v;
	set<pii>::iterator it;
	// Calculate value of pref and suff
	if ( par[u] == '(' ){
		suff[u] = 0;
		it = S.lower_bound( pii( f[u] , INT_MAX ) );
		if ( it == S.end() || it->first > (f[u] + 1) ){
			pref[u] = d[u] + 1;
		}
		else {
			pref[u] = d[u] - it->second - 1;
		}
	}
	else {
		pref[u] = 0;
		it = S.lower_bound( pii( f[u] - 2, INT_MAX ) );
		if ( it == S.end() || it->first >= f[u] ){
			suff[u] = d[u] + 1;	
		}
		else {
			suff[u] = d[u] - it->second - 1;
		}
	}
	// Insert pair ( f, depth )
	S.insert( pii( f[u] , d[u] ) );
	for ( int i=0; i < (int) T[u].size(); ++i ){
		v = G[u][i];
		if ( v != p )	dfs( v , u );
	}
	// delete pair ( f, depth )
	S.erase( pii( f[u] , d[u] ) );
}

void precalc(){
	for ( int i=1; i <= N; ++i )
		for ( int j=1; (1<<j) <= N; ++j )
			P[i][j] = 0;

	for ( int j=1; (1<<j) <= N; ++j )
		for ( int i=1; <= N; ++i )
			if ( P[i][j-1] > 0 )
				P[i][j] = P[ P[i][j-1] ][ j - 1 ];
}

int lca( int u, int v ){
	if ( d[u] < d[v] ) swap(u, v);
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
	int u, v;
	
	d[0] = -1;
	scanf("%d", &runs);	
	while ( runs-- ){
		scanf("%d %d", &N, &Q);
		for ( int i=1; i < N; ++i ){
			scanf("%d %d", &u, &v);
			T[u].push_back(v), T[v].push_back(u);
		}
		scanf("%s", &par[1]);
		// Calculate depth, f, pref, suff
		dfs(1, 0);	
		// For LCA computation		
		precalc();
		int p;
		//	Answer the queries
		while ( Q-- ){
			scanf("%d %d", &u, &v);
			if ( d[u] < d[v] ) swap(u, v);
			w = lca( u , v );
			p = P[w][0];	
			if ( w == v ){
				if ( pref[u] >= d[u] - d[p] && f[u] - f[p] == 0 ){
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
	}
	return 0;
}
