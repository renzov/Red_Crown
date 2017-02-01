#include<cstdio>
char M[105][105];
bool visited[105][105];
int r,c;
int dx[]={1,1,0,-1,-1,-1,0,1};
int dy[]={0,-1,-1,-1,0,1,1,1};

int dfs(int y,int x){
  visited[y][x] = true;
  int ny,nx;
  int res = 1;
  for (int i=0; i < 8; ++i){
	 nx = x + dx[i];
	 ny = y + dy[i];
	 //printf("testing %d %d\n",ny,nx);
	 if (ny<0 || nx<0 || ny>=r || nx>=c) continue;
	 //puts("Paso");
	 //printf("%d %d\n",ny,nx);
	 if (!visited[ny][nx] && M[ny][nx] == '*'){
		//puts("Entro");
		res += dfs(ny,nx);
	 }
  }
  return res;
}

int main(){
  while (scanf("%d %d",&r,&c) && (r || c)){
	 for (int i=0; i < r; ++i){
		for (int j=0; j < c; ++j){
			 scanf(" %c",&M[i][j]);
			 visited[i][j] = false;
		}
	 }
	 int res = 0;
	 for (int i=0; i < r; ++i){
		for (int j=0; j < c; ++j){
			 if (!visited[i][j] && M[i][j] == '*'){
				  //printf("entraste %d %d\n",i,j);
				  if (dfs(i,j) == 1) res++;
			 }
		}
	 }
	 printf("%d\n",res);
  }
  return 0;
}