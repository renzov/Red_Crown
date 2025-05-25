#include<cstdio>
#include<vector>
#include<climits>
#include<algorithm>

using namespace std;
const int MAXN = 100005;
typedef pair<int , int> pii;
typedef pair<int, pii> edge;
int N, M, K;

vector<int> T[MAXN];
vector<int> G[MAXN];
vector<int> W[MAXN];

int L[MAXN];
int R[MAXN];

int num;
edge E[MAXN];

int cnt[MAXN];
int B[MAXN];
long long sum[MAXN];

void dfs( const int &u, const int &p ){
	int v;
	int idx = -1; // index of parent
	L[u] = R[u] = num++;
	for ( int i=0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		if ( v == p ){ 
			idx = i;
			continue;
		}
		dfs( v, u );
		R[u] = R[v];
	}
	if ( idx >= 0 ){
		// make the parent the last element in the adjacency list
		for ( int i=idx; i < (int)T[u].size() - 1; ++i )
			swap( T[u][i], T[u][i + 1] );
	}
}

long long solve( const int &u ){
	int S = T[u].size();
	for ( int i=0; i < S; ++i ){
		cnt[i] = 0;
		sum[i] = 0;
		B[i] = R[ T[u][i] ];
	}

	int w, v;
	int idx;

	for ( int i=0; i < (int) G[u].size(); ++i ){
		v = G[u][i];
		w = W[u][i];
		if ( L[v] >= L[u] && L[v] <= R[u] ){	// search for index of subtree
			idx = lower_bound( B, B + (S - 1), L[ v ] ) - B;
			cnt[idx]++;
			if ( cnt[idx] <= K ) sum[ idx ] += w;
		}
		else {
			cnt[S - 1]++;
			if ( cnt[S - 1] <= K ) sum[S - 1] += w;
		}
	}
	long long res = LLONG_MAX;
	for ( int i=0; i < S; ++i )
		if ( cnt[i] >= K ) res = min( res, sum[i] );
	return res;
}

int main(){
	scanf("%d %d %d", &N, &M, &K);
	
	int u, v, w;
	for ( int i=1; i < N; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		T[u].push_back( v );
		T[v].push_back( u );
	}
	
	num = 0;
	dfs( 0, -1 );

	for ( int i=0; i < M; ++i ){
		scanf("%d %d %d", &u, &v, &w);
		u--, v--;
		E[i].first = w;
		E[i].second.first = u;
		E[i].second.second = v;
	}
	sort( E , E + M );
	for ( int i=0; i < M; ++i ){
		w = E[i].first;
		u = E[i].second.first;
		v = E[i].second.second;
		G[u].push_back( v );	W[u].push_back( w );
		G[v].push_back( u );	W[v].push_back( w );
	}
	long long res = LLONG_MAX;
	for ( int i=0; i < N; ++i ){
		if ( (int)G[u].size() >= K )
			res = min( res, solve( i ) );
	}
	printf("%lld\n", res);
	return 0;
}
