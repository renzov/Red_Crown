#include<cstdio>
#include<algorithm>
using namespace std;
typedef pair<int,int> pii;
typedef pair<int, pii> edge;
const int MAXN = 100005;
const long long MOD = 1000000000;
int f[MAXN];
int size[MAXN];
long long sum[MAXN];
edge E[MAXN];

inline int find_set( const int &x ){
	return x == f[x]? x:(f[x] = find_set( f[x] ));
}

int main(){
	int N, M;
	int u, v, w;

	scanf("%d %d", &N, &M);
	for ( int i=0; i < M; ++i ){
		scanf("%d %d %d", &u, &v, &w);
		u--, v--;
		E[i] = edge( w, pii( u, v ) );
	}
	sort( E, E + M );
	// Compute partial sums
	sum[0] = E[0].first;
	for ( int i=1; i < M; ++i ){
		sum[i] = sum[i - 1] + E[i].first;
		sum[i] %= MOD;
	}
	// Initialize union find
	for ( int i=0; i < N; ++i )
		f[i] = i, size[i] = 1;
	// Find the answer
	long long res = 0;
	long long delta;
	for ( int i=M - 1; i >= 0; --i ){
		u = E[i].second.first, v = E[i].second.second;
		u = find_set( u ), v = find_set( v );
		if ( u != v ){
			delta = (1LL * size[u] * size[v]) % MOD;
			delta *= sum[i];
			delta %= MOD;
			res += delta;
			res %= MOD;
			f[v] = u, size[u] += size[v]; 
		}
	}
	printf("%lld\n", res);
	return 0;
}
