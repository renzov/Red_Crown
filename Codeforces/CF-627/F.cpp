#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int MAXN = 200005;
int N;
vector<int> T[MAXN];
int down[MAXN];
int res[MAXN];
int A[MAXN];

void dfs1( const int &u, const int &p ){
	int v;
	down[u] = A[u] == 1? 1:-1;
	for ( int i=0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		if ( v == p ) continue;
		dfs1( v, u );
		if ( down[v] > 0 ) down[u] += down[v];
	}
}

void dfs2( const int &u, const int &p, const int &bestUp ){
	int v, newBest;
	res[u] = down[u] + bestUp;

	for ( int i=0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		if ( v == p ) continue;
		newBest = bestUp + down[u] - (down[v] > 0? down[v]:0);
		dfs2( v, u, max( 0, newBest ) );
	}
}


int main(){
	int u, v;
	scanf("%d", &N);
	for ( int i=0; i < N; ++i )
		scanf("%d", A + i);
	for ( int i=1; i < N; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		T[u].push_back(v), T[v].push_back(u);
	}

	dfs1(0, -1);
	dfs2(0, -1, 0);
	for ( int i=0; i < N; ++i ){
		if ( i ) putchar(' ');
		printf("%d", res[i]);
	}
	puts("");
	return 0;

}
