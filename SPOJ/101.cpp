#include<cstdio>
#include<algorithm>
using namespace std;
const int INF = 99999999;
int T[55][55];
int G[55][55];
pair<int,int> memo[55][1005];
int n;

pair<int,int> solve(int u,int t){
  if (t < 0) return make_pair(INF,INF);
  if ( u==n-1 ) return make_pair(0,0);
  if (memo[u][t].first != -1) return memo[u][t];
  pair<int,int> res = make_pair(INF,INF);
  pair<int,int> next;
  for (int v=0; v < n; ++v){
	 if (u!=v){
		next = solve(v,t-T[u][v]);
		if ( (next.first + G[u][v]) < res.first ){
			 res.first = next.first + G[u][v];
			 res.second = next.second + T[u][v];
		}
	 }
  }
  memo[u][t] = res;
  return memo[u][t];
}

int main(){
  int t;
  while (scanf("%d %d",&n,&t) && n){
	 for (int i=0; i < n; ++i)
		for (int j=0; j < n; ++j)
		  scanf("%d",&T[i][j]);
	 for (int i=0; i < n; ++i)
		for (int j=0; j < n; ++j)
		  scanf("%d",&G[i][j]);
	 for (int i=0; i < n; ++i)
		for (int j=0; j <= t; ++j){
		  memo[i][j].first = -1;
		  memo[i][j].second = -1;
		}
	 pair<int,int> res = solve(0,t);
	 printf("%d %d\n",res.first,res.second);
  }
  return 0;
}