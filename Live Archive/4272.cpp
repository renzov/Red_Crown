#include<cstdio>
#include<vector>
using namespace std;
const int MAXN = 102;
int st;
int S[MAXN];
bool in[MAXN];
int low[MAXN];
int number[MAXN];
int scc[MAXN];
int num;
int nc;
int res;
vector<int> G[MAXN];
bool T[MAXN][MAXN];
bool R[MAXN][MAXN];

inline int Min(int x,int y){ return x<=y? x:y; }

void strong_connect(int u){
	int i;	
	int v;
	int nodes;

	number[u] = low[u] = num++;
	in[u] = true;
	S[st++] = u;
	for (i=0; i < G[u].size(); ++i){
		v = G[u][i];
		if ( number[v] < 0 ){
			strong_connect(v);
			low[u] = Min(low[u],low[v]);
		}
		else if (number[v] < number[u] && in[v]){
			low[u] = Min(low[u],number[v]);
		}
	}
	if ( number[u] == low[u] ){
		nodes = 0;		
		while ( st > 0 && number[ S[st-1] ] >= number[u] ){
			v = S[st-1];
			scc[v] = nc;
			in[v] = false;
			st--;
			nodes++;
		}
		nc++;
		if ( nodes > 1 ) res += nodes;
	}
}

int main(){
	int n,m;
	int u,v;
	int i,j,k;
	int cases = 0;
	while (scanf("%d %d",&n,&m) && n){
		cases++;		
		/* Initialize */
		st = 0;
		for (i=0; i < n; ++i){
			G[i].clear();
			in[i] = false;
			number[i] = -1;
			low[i] = -1;
			scc[i] = -1;
		}
		for (i=0; i < n; ++i)
			for (j=0; j < n; ++j)
				T[i][j] = R[i][j] = false;

		for (i=0; i < m; ++i){
			scanf("%d %d",&u,&v);
			u--,v--;
			G[u].push_back(v);
		}	
		res = nc = num = 0;
		for (i=0; i<n; ++i){
			if ( number[i] < 0) strong_connect(i);
		}
		/* Creating DAG */
		for ( u = 0; u < n; ++u ){
			for (i=0; i < G[u].size(); ++i){
				v = G[u][i];
				if ( scc[u] != scc[v] ){
					T[ scc[u] ][ scc[v] ] = true; 
				}
			}
		}
		n = nc;
		/* Creating copy */
		for (i=0; i < n; ++i)
			for (j=0; j< n; ++j)
				R[i][j] = T[i][j];
		/* Transitive Clousure */
		for (k=0; k < n; ++k)
			for (i=0; i < n; ++i)
				for (j=0; j < n; ++j)
					T[i][j] |= ( T[i][k] & T[k][j] );
		/* Removing edges */
		for (i=0; i < n; ++i){
			for (j=0; j < n; ++j){
				if ( i != j && R[i][j] ){
					for (k=0; k < n; ++k){
						if ( k != i && k != j && (T[i][k] && T[k][j]) ){
							R[i][j] = false;
							break;
						}
					}
				}
			}
		}
		/* Counting the remaining edges */
		for (i=0; i < n; ++i)
			for (j=0; j < n; ++j)
				if ( R[i][j] ) res++;
		printf("Case %d: %d\n",cases,res);
	}
	return 0;
}
