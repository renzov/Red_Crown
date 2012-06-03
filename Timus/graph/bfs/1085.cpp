#include<cstdio>
#include<queue>
#include<climits>
using namespace std;

int n;
int d[105][105];
int G[105][105] = {0};

int bfs(int s,int p){
  for (int i=1; i <= n; ++i) d[p][i] = -1;
  d[p][s] = 0;
  queue<int> q;
  q.push(s);
  int u; 
  while (!q.empty()){
	 u = q.front();
	 q.pop();
	 for (int v=1; v <= n; ++v){
		if (G[u][v] && d[p][v] == -1){
		  d[p][v] = d[p][u] + 4;
		  q.push(v);
		}
	 }
  }
  for (int i=1; i <= n; ++i)
	 if (d[p][i] == -1) d[p][i] = INT_MAX;
}

int main(){
  
  int lst[105];
  int mon[105];
  int t[105];
  int start;
  int m;
  scanf("%d %d",&n,&m);
  for (int i=0; i < m; ++i){
	 scanf("%d",&lst[0]);
	 for (int j=1; j <= lst[0]; ++j){
		scanf("%d",&lst[j]);
		for (int k=1; k < j; ++k){
		  G[ lst[j] ][ lst[k] ] = G[ lst[k] ][ lst[j] ] = 1;
		}
	 } 
  }
  int k;
  scanf("%d",&k);
  for (int i=0; i < k; ++i){
	 scanf("%d %d %d",&mon[i],&start,&t[i]);
	 bfs(start,i);
  }

  int mini = INT_MAX;
  int len;
  int res;
/*
  for (int i=0; i < k; ++i){
	 for (int j=1; j <= n; ++j){
		if (d[i][j] < INT_MAX) printf(" %d",d[i][j]);
		else printf(" -1");  
	 }
	 putchar('\n');
  }
*/  
  for (int i=1; i <= n; ++i){
	 len = 0;
	 for (int j=0; j < k; ++j){
		if (t[j] == 0){
		  if (d[j][i] > mon[j]){
			 len = INT_MAX;
			 break;
		  }
		  else {
			 len += d[j][i];
		  }
		}
		else if (d[j][i]==INT_MAX){
			 len = INT_MAX;
			 break;
		}
	 }
	 if (len < mini){ mini = len; res = i; }
  }
  if (mini < INT_MAX) printf("%d %d\n",res,mini);
  else printf("0\n");

  return 0;
}