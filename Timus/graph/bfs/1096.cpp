#include<cstdio>
#include<vector>
#include<queue>
using namespace std;

vector<int> G[ 1005 ];
int p[ 1005 ][ 2 ];
int n;
int e;
int last;
int d[ 1005 ];
int pred[ 1005 ];

int bfs(){
  d[0] = 0;
  pred[0] = -1;
  queue<int> q;
  q.push(0);
  int u,v;

  while (!q.empty()){
		u = q.front();
		q.pop();
		if (p[u][0]==e || p[u][1]==e){ last = u; return d[u]; }
		for (int i=0; i < G[u].size(); ++i){
		  v = G[u][i];
		  if (d[v]==-1){
			 d[v] = d[u]+1;
			 pred[v] = u;
			 q.push(v);
		  }
		}
  }
  return -1;
}

void printSol(int u){
  if (pred[u]!=-1){
	 printSol(pred[u]);
	 printf("%d\n",u);
  }
}

int main(){
  
  scanf("%d",&n);

  for (int i=1; i <= n; ++i){
	 d[i] = -1;
	 pred[i] = -1;
	 scanf("%d %d",&p[i][0],&p[i][1]);
  }
  scanf("%d %d %d",&e,&p[0][0],&p[0][1]);
  
  for (int i=0; i <= n; ++i){
	 for (int j=0; j <= n; ++j){
		if (i!=j && (p[i][0]==p[j][0] || p[i][1]==p[j][0]) 
		  //  p[i][1]==p[j][0] || p[i][1]==p[j][1]
		   ){
			 G[i].push_back(j);
		}
	 }
  }

  int res = bfs();
  if (res < 0) printf("IMPOSSIBLE\n");
  else { printf("%d\n",res); printSol(last); }

  return 0;
}