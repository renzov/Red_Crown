#include<cstdio>
char M[60][60];
bool visited[60][60];
int res;
int r,c;
int dx[]={1,0,-1,0};
int dy[]={0,-1,0,1};

char get_char(int y,int x){
  if (x<0||y<0||x>=c||y>=r) return (char)0;
  return M[y][x];
}

void dfs(int y,int x){
  visited[y][x] = true;
  if (get_char(y,x) == 'G') res++;
  bool advance=true;
  int nx,ny;
  char c;
  for (int i=0; i<4 && advance; ++i){
	 nx = x + dx[i];
	 ny = y + dy[i];
	 if (get_char(ny,nx) == 'T') advance=false;
  }
  if (!advance) return;
  for (int i=0; i<4; ++i){
	 nx = x + dx[i];
	 ny = y + dy[i];
	 c = get_char(ny,nx);
	 if ((c == '.' || c == 'G') && !visited[ny][nx]) 
		dfs(ny,nx);
  }
}

int main(){

  while (scanf("%d %d",&c,&r) != EOF){
		for (int i=0; i<r; ++i) 
		  for (int j=0; j < c; ++j){
				scanf(" %c",&M[i][j]);
				visited[i][j] = false;
		  }
		res = 0;
		for (int i=0; i < r; ++i){
			 for (int j=0; j < c; ++j){
				  if (M[i][j] == 'P')
					 dfs(i,j);
			 }
		}
		printf("%d\n",res);
  }

  return 0;
}