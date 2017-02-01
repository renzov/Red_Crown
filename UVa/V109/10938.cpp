#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

int P[5005][50];
int T[5005];
int L[5005];
vector<int> G[5005];
int n;

void dfs(int u,int p){
  int v;
  for (int i=0; i < G[u].size(); ++i){
	 v = G[u][i];
	 if (v != p){
		  T[v] = u;
		  L[v] = L[u] + 1;
		  dfs(v,u);
	 }
  }
}

void preprocess(){
  for (int i=0; i < n; ++i)
	 for (int j=0; (1<<j) < n; ++j)
		  P[i][j] = -1;

  for (int i=0; i < n; ++i)
	 P[i][0] = T[i];

  for (int j=1; (1<<j) < n; ++j)
		for (int i=0; i < n; ++i)
		  if (P[i][j-1] != -1)
			 P[i][j] = P[ P[i][j-1] ][j-1];
}

void query(int p,int q){
  int i,log,tmp;
  
  if (p==q){ printf("The fleas meet at %d.\n",p+1); return; }
  
  if (L[p] < L[q])
	 tmp=q,q=p,p=tmp;

  int p1 = p;
  int q1 = q;

  for (log = 1; (1<<log) <= L[p]; log++);
  log--;

  for (i=log; i >= 0; --i)
		if (L[p] - (1<<i) >= L[q])
			 p = P[p][i];

  int d;
  bool even = true;
  
  if (p==q){
		d = L[p1] - L[p]; 
		if (d%2) even = false;
		d/=2;
		for (i=log; i >= 0; --i){
			 if ((1<<i) <= d){ p1 = P[p1][i]; d -= (1<<i); }
		}
		if (even) printf("The fleas meet at %d.\n",p1+1);
		else printf("The fleas jump forever between %d and %d.\n",min(p1+1,T[p1]+1),max(p1+1,T[p1]+1));
  }
  else {
		for (i=log; i >= 0; --i)
		  if (P[p][i] != -1 && P[p][i] != P[q][i])
			 p=P[p][i],q=P[q][i];
		p = T[p];
		d = (L[p1] - L[p]) + (L[q1] - L[p]);
		if (d%2) even = false;
		d/= 2;
		
		for (i=log; i >= 0; --i){
			 if ((1<<i) <= d){ p1 = P[p1][i]; d -= (1<<i); }
		}
		if (even) printf("The fleas meet at %d.\n",p1+1);
		else printf("The fleas jump forever between %d and %d.\n",min(p1+1,T[p1]+1),max(p1+1,T[p1]+1));
  }

}

int main(){
  int u,v;
  int q;

  while (scanf("%d",&n) && n ){
		for (int i=0; i < n; ++i){
			 T[i] = -1;
			 L[i] = 0;
			 G[i].clear();
		}
		for (int i=1; i < n; ++i){
			 scanf("%d %d",&u,&v);
			 u--,v--;
			 G[u].push_back(v);
			 G[v].push_back(u);
		}
		dfs(0,-1);
		
		preprocess();
		
		scanf("%d",&q);
		for (int i=0; i < q; ++i){
			 scanf("%d %d",&u,&v);
			 u--,v--;
			 query(u,v);
		}
  }

  return 0;
}