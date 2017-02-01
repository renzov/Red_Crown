#include<cstdio>
#include<vector>
#include<queue>
using namespace std;

const int MAX = 10002;
vector<int> G[MAX];
int d[MAX];
int frec[MAX];
int n,s;

int bfs(int st){
  queue<int> q;
  for(int i=1; i<=n; ++i) d[i]=-1;
  d[st] = 0;
  q.push(st);
  int u,v;
  while (!q.empty()){
	 u=q.front();
	 q.pop();
	 for (int i=0; i < G[u].size(); ++i){
		v = G[u][i];
		if (d[v]<0){	d[v]=d[u]+1; q.push(v);	}
	 }
  }
  int sum = 0;
  for (int i=1; i<=n; ++i)
	 if (frec[i] >= 2) sum+=d[i];
  return sum;
}

int main(){

  int runs;
  int act;
  int prev;

  scanf("%d",&runs);
  while (runs--){
	 scanf("%d %d",&n,&s);
	 for (int i=1; i <= n; ++i){	G[i].clear();	frec[i] = 0;	}
	 for (int i=0;	i < s; ++i){
		scanf("%d",&act);
		frec[act]++;
		prev = act;
		while (scanf("%d",&act) && act){
		  G[act].push_back(prev);
		  G[prev].push_back(act);
		  frec[act]++;
		  prev = act;
		}
	 }
	 int mini = 99999999;
	 int res;
	 int tmp;
	 for (int i=1; i<=n; ++i){
		if (frec[i] >= 2){
		  tmp = bfs(i);
		  if (tmp < mini){
			 res = i;
			 mini = tmp;
		  }
		}
	 }
	 printf("Krochanska is in: %d\n",res);
  }

  return 0;
}