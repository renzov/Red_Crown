#include<cstdio>
#include<vector>
using namespace std;

const int MAXN = 100005;
int W[MAXN];
int nxt[MAXN];
int Tw[MAXN];
vector<int> T[MAXN];

void dfs( const int &u ){
	if ( (int)T[u].size() == 0 ){
		nxt[u] = -1;
		Tw[u] = W[u];
		return; 
	}
	int v;
	int best = -1;
	Tw[u] = W[u];
	for ( int i=0; i < (int) T[u].size(); ++i ){
		v = T[u][i];
		dfs( v );
		Tw[u] += Tw[v];
		if ( best == -1 ){
			best = v;
		}
		else if ( Tw[best] < Tw[v] ){
			best = v;
		}
		else if ( Tw[best] == Tw[v] && v > best ){
			best = v;
		}
	}
	nxt[u] = best;
}

void process(){
	int r;
	int d;
	int u, v;
	int N;

	scanf("%d %d", &N, &r);
	for ( int i=0; i < N; ++i ){
		scanf("%d", W + i);
		scanf("%d", &d);
		while ( d-- ){
			scanf("%d", &v);
			T[i].push_back( v );
		}
	}
	dfs( r );

	int res = W[r];
	u = r;
	do {
		u = nxt[u];
		res += W[u];
	}
	while ( nxt[u] != -1 );
	printf("%d\n", res);

	bool first = true;
	int cnt = 0;
	u = r;
	while ( u != -1 ){
		if ( !first ) putchar(' ');
		printf("%d", u);
		if ( first ) first = false;
		cnt++;
		u = nxt[u];
		if ( cnt == 10 ){
			puts("");
			first = true;
			cnt = 0;
		}
	}
	if ( cnt > 0 ) puts("");
	// Clear memory
	for ( int i=0; i < N; ++i ){
		T[i].clear();
		Tw[i] = 0;
	}
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- ) process();
	return 0;
}
