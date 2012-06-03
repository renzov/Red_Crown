#include<cstdio>
#include<vector>
using namespace std;
vector< pair<int,int> > G[100][100];
int coin[100][100];
int d[100][100];

int n = 0;

int dfs(int x,int y){
  d[y][x] = coin[y][x];
  int maxi = 0;
  int ny,nx;
  for (int i=0; i < G[y][x].size(); ++i){
	 nx = G[y][x][i].first;
	 ny = G[y][x][i].second;
	 if (d[ny][nx] == -1) dfs(nx,ny);
	 if (d[ny][nx] > maxi) maxi = d[ny][nx];
  }
  d[y][x] += maxi;
  return d[y][x];
}

int main(){

  int runs;
  int k;
  int nx,ny;
  int res;

  scanf("%d",&runs);
  while (runs--){
	
	 scanf("%d %d",&n,&k);
	 for (int i=0; i < n; ++i)
		for (int j=0; j < n; ++j){
		  scanf("%d",&coin[i][j]);
		  d[i][j] = -1;
		}
	 
	 for (int i=0; i < n; ++i)
		for (int j=0; j < n; ++j){
			 
			 for (int dx=-k; dx <= k; dx++){
				nx = j + dx;
				if (nx < 0 || nx >= n) continue;
				if (coin[i][nx] > coin[i][j]){
				  G[i][j].push_back( make_pair(nx,i) );
				}
			 }
			 
			 for (int dy=-k; dy <= k; dy++){
				ny = i + dy;
				if (ny < 0 || ny >= n) continue;
				if (coin[ny][j] > coin[i][j]){
				  G[i][j].push_back( make_pair(j,ny) );
				}
			 }

		}
	 
	 res = dfs(0,0);
	 	 
	 printf("%d\n",res);

	 if (runs){ 
		putchar('\n'); 
		for (int i=0; i<n; ++i)
		  for (int j=0; j < n; ++j)
			 G[i][j].clear();
	 }
  }

  return 0;
}