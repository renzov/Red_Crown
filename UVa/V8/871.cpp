#include<cstdio>
#include<climits>
#include<cstring>
int r,c;
char M[50][50];
bool visited[50][50];

int dx[]={1,1,0,-1,-1,-1,0,1};
int dy[]={0,-1,-1,-1,0,1,1,1};

int dfs(int y,int x){
  visited[y][x] = true;
  int ny,nx;
  int res = 1;
  for (int i=0; i < 8; ++i){
		nx = x + dx[i];
		ny = y + dy[i];
		if (nx < 0 || nx >= c || ny >= r || ny < 0) continue;
		if (!visited[ny][nx] && M[ny][nx] == '1') res += dfs(ny,nx);
  }
  return res;
}

int main(){
  int runs;
  scanf("%d",&runs);
  while (getchar() != '\n');
  while (getchar() != '\n');
  while (runs--){
		r = 0;
		while (gets(M[r])){
			 if (!M[r][0]) break;
			 r++;
		}
		c = strlen(M[0]);
		for (int i=0; i < r; ++i)
		  for (int j=0; j < c; ++j)
				visited[i][j] = false;
		int res = 0;
		int s;
		for (int i=0; i < r; ++i){
			 for (int j=0; j < c; ++j){
				  if (!visited[i][j] && M[i][j] == '1'){
						s = dfs(i,j);
						if (s>res) res = s; 
				  }
			 }
		}
		printf("%d\n",res);
		if (runs) putchar('\n');
  }
  return 0;
}