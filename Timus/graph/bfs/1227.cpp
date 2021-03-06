#include<cstdio>

int n,m,s;
int G[105][105] = {0};
int d[105];

bool cycle,multi,loop;
int last;
int diameter;

void dfs(int u,int pred){
  for (int v=0; v < n && !cycle; ++v){
	 if (v!=pred && v!=u && G[u][v]){
		  if (d[v]!=-1){
			 cycle = true;
		  }
		  else {
				d[v] = G[u][v] + d[u];
				if (d[v] > diameter){
					 last = v;
					 diameter = d[v];
				}
				dfs(v,u);
		  }
	 }
  }
  d[u] = -1;
}


int main(){
  int u,v,w;
  cycle = multi = loop = false;
  scanf("%d %d %d",&n,&m,&s);
  for (int i=0; i < m && !loop && !multi; ++i){
		scanf("%d %d %d",&u,&v,&w);
		u--,v--;
		if (u == v) loop = true;
		if (G[u][v] > 0) multi = true;
		G[u][v] = G[v][u] = w;
  }
  if (multi || loop){ 
		printf("YES\n");
		return 0;
  }
  for (int i=0; i < n; ++i){
	 d[i] = -1;
  }
  int longest = 0;
  for (int i=0; i < n && !cycle; ++i){
		if (d[i]==-1){
			 diameter = 0;
			 d[i] = 0;
			 dfs(i,-1);
			 if (!cycle){
				  diameter = 0;
				  d[last] = 0;
				  dfs(last,-1);
				  if (diameter > longest) longest = diameter;
			 }
		}
  }
  if (cycle) printf("YES\n");
  else printf( (longest >= s)? "YES\n":"NO\n");

  return 0;
}