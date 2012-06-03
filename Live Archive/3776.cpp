#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int n;
vector<int> G[505];
int a[505][3];
int d[505];

inline bool inside(int x,int y){
  return a[x][0] < a[y][0] && a[x][1] < a[y][1] && a[x][2] < a[y][2];
}

void dfs(int u){
  int i;
  int v;
  int best = 0;
  for (i=0; i<G[u].size(); ++i){
	 v = G[u][i];
	 if ( d[v] == -1 ) dfs(v);
	 if ( d[v] > best ) best = d[v];
  }
  d[u] = best + 1;
}

int main(){
  int i,j,res;
  scanf("%d",&n);
  while ( n > -1 ){
	 for (i=0; i < n; ++i){
		d[i] = -1;
		scanf("%d x %d x %d",&a[i][0],&a[i][1],&a[i][2]);
		if ( a[i][0] > a[i][1] ) swap( a[i][0] , a[i][1] );
		if ( a[i][0] > a[i][2] ) swap( a[i][0] , a[i][2] );
		if ( a[i][1] > a[i][2] ) swap( a[i][1] , a[i][2] );
		for (j=0 ; j < i ; ++j){
		  if ( inside(i,j) ) G[j].push_back(i);
		  else if ( inside(j,i) ) G[i].push_back(j);
		}
	 }
	 res = 0;
	 for (i=0; i < n; ++i){
		if ( d[i] == -1 ) dfs(i);
		if ( d[i] > res ) res = d[i];
	 }
	 printf("%d\n",res);
	 scanf("%d",&n);
	 if ( n > -1 ) for (i=0; i < n; ++i) G[i].clear();
  }
  return 0;
}