#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

const int MAXN = 2005;
vector<int> G[MAXN];
int indeg[MAXN];
int L[MAXN] = {0};

void dfs( int u, int p ){
	if ( p == -1 ) L[u] = 1;
	else L[u] = L[p] + 1;

	for ( int i=0; i < (int) G[u].size(); ++i )
		dfs( G[u][i] , u );

}

int main(){
	int N;
	int p;
 
	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d", &p);
		p--;
		if ( p >= 0 ){
			G[p].push_back(i);
			indeg[i]++;
		}
	}
	for ( int i=0; i < N; ++i )
		if ( indeg[i] == 0 )
			dfs( i, -1 );

	printf("%d\n", *max_element(L, L + N));

	return 0;
}
