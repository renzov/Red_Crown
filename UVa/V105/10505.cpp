#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;

const int WHITE = 0;
const int BLACK = 1;
const int GRAY = 2;

int G[205][205];
int color[205];
int n;
int w,b;
bool bipartite;
int visited[205];

void dfs(int u,int c){
	if (visited[u]){
		if (color[u] != c) bipartite = false;
		return;
	}
	color[u] = c;
	visited[u] = 1;
	
	if (c==WHITE) w++;
	else b++;
	
	for (int v=1; v <= n; ++v){
		if (G[u][v]){
			dfs(v,1-c);
		}
	}
}

int main(){
	int m;
	int v;
	int runs;
	
	scanf("%d",&runs);
	while (runs--){
		scanf("%d",&n);
		memset(G,0,sizeof(G));
		
		for (int u=1; u <= n; ++u){
			color[u] = GRAY;
			visited[u] = 0;
			scanf("%d",&m);
			while (m--){
				scanf("%d",&v);
				if (v <= n && v >= 1)
					G[u][v] = G[v][u] = 1;
			}
		}
		int res = 0;
		for (int u=1; u <= n; ++u){
			if (!visited[u]){
				w = 0;
				b = 0;
				bipartite = true;
				dfs(u,WHITE);
				if (bipartite)
					res += max(w,b);
			}
		}
		cout << res << endl;
	}

	return 0;
}
