#include<cstdio>
#include<cstdlib>
using namespace std;
const int MAXN = 10005;

int deg[MAXN];

int main(){
	freopen("matrix.in", "r", stdin);
	freopen("matrix.out", "w", stdout);

	int N, M;
	int u, v;

	scanf("%d %d", &N, &M);
	while ( M-- ){
		scanf("%d %d", &u, &v);
		u--, v--;
		deg[u]++, deg[v]++;
	}

	long long ans = 0;
	for ( int i = 0; i < N; ++i )
		ans += (deg[i] * deg[i]);

	printf("%lld\n", ans);
	return 0;
}
