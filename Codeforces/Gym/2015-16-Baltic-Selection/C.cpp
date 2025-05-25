#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

const int MAXN = 100005;
typedef pair<int, int> pii;

int N, K, L;
vector<int> T[MAXN];
int P[MAXN];
int A[MAXN];
int H[MAXN];
int deg[MAXN];

void dfs( const int &u ){
	int v;
	for ( int i = 0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		if ( (int)T[u].size() > 1 )
			H[v] = H[u] + 1;
		else
			H[v] = H[u];
		dfs(v);
	}
}

int solve( const int &h, const int &sense ){

	priority_queue<pii> Q;
	for ( int i = 0; i < N; ++i ){
		deg[i] = (int)T[i].size();
		if ( !deg[i] ){
			Q.push( pii( A[i] * sense, i ) );
		}
	}
	
	int u, w, p;
	while ( !Q.empty() ){
		u = Q.top().second;
		w = Q.top().first;
		Q.pop();
		if ( H[u] <= h )
			return w * sense;
		p = P[u];
		deg[p]--;
		if ( !deg[p] )
			Q.push( pii( w, p ) );
	}
	return 0;
}

int main(){
	int p;

	scanf("%d %d", &N, &K);
	for ( int i = 1; i < N; ++i ){
		scanf("%d", &p);
		p--;
		P[i] = p;
		T[p].push_back(i);
	}

	L = 0;
	for ( int i = 0; i < N; ++i ){
		scanf("%d", A + i);
		if ( A[i] ) L++;
	}
	// find height of each vertex
	H[0] = 0;
	dfs(0);
	printf("%d %d\n", solve( K, -1 ), solve( N - L - K, 1 ) );
	return 0;
}
