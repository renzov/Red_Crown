#include<cstdio>
int dx[]={1,0,-1,0};
int dy[]={0,-1,0,1};
bool visited[25][25];
int r,c;
char land;
char M[25][25];

int dfs(int y,int x){
  visited[y][x] = true;
  int res = 1;
  int nx,ny;
  for (int i=0; i<4; ++i){
	 ny = y + dy[i];
	 nx = x + dx[i];
	 if (ny >= r || ny < 0) continue;
	 if (nx < 0) nx = c-1;
	 else if (nx >= c) nx = 0;
	 if (!visited[ny][nx] && M[ny][nx]==land)
		res += dfs(ny,nx);
  }
  return res;
}

int main(){
  int tmp;
  int y,x;
  while (scanf("%d %d",&r,&c) != EOF){
		for (int i=0; i < r; ++i){
		  for (int j=0; j < c; ++j){
			 scanf(" %c",&M[i][j]);
			 visited[i][j] = false;
		  }
		}
		scanf("%d %d",&y,&x);
		land = M[y][x];
		dfs(y,x);
		int res = 0;
		for (int i=0; i < r; ++i){
		  for (int j=0; j < c; ++j){
			 if (M[i][j] == land && !visited[i][j]){
				  tmp = dfs(i,j);
				  if (tmp > res) res = tmp;
			 }
		  }
		}
		printf("%d\n",res);
  }
  return 0;
}