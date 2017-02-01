#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;

int op[102];
int d[1<<15];
int n,m;

int bfs(){
  queue<int> q;
  int start = (1 << n) - 1;
  d[start] = 0;
  q.push( start );
  int u,v;
  while (!q.empty()){
	 u = q.front(); q.pop();
	 if (u==0) break;
	 for (int i=0; i < m; ++i){
		v = u ^ op[i];
		if (d[v] == -1){
		  d[v] = d[u] + 1;
		  q.push(v);
		}
	 }
  }
  return d[0];
}

int main(){

  int runs;
  int b;
  int res;

  scanf("%d",&runs);
  for (int k=1; k <= runs; ++k){
		scanf("%d %d",&n,&m);
		memset(d,-1,sizeof(int)*(1<<n));
		for (int i=0; i < m; ++i){
			 op[i] = 0;
			 for (int j=0; j < n; ++j){
				  scanf("%d",&b);
				  if (b) op[i] |= (1<<j);
			 }
		}
		res = bfs();
		if (res < 0) printf("Case %d: IMPOSSIBLE\n",k);
		else printf("Case %d: %d\n",k,res);
  }
  return 0;
}