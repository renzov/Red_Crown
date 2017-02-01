#include<cstdio>
#include<queue>
using namespace std;
int n,m;
int d[200][200];
int dx[] = {1,0,-1,0};
int dy[] = {0,-1,0,1};

void bfs(){
  char s[200];
  queue< pair<int,int> > q;
  for (int i=0; i < n; ++i){
	 scanf("%s",s);
	 for (int j=0; j < m; ++j) 
		  if (s[j] == '1'){ d[i][j] = 0; q.push( make_pair(i,j) ); }
  }
  int x,y;
  int nx,ny;
  while (!q.empty()){
	 x = q.front().second;
	 y = q.front().first;
	 q.pop();
	 for (int i=0; i < 4; ++i){
		  nx = x + dx[i];
		  ny = y + dy[i];
		  if (nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
		  if (d[ny][nx] == -1){
				d[ny][nx] = d[y][x] + 1;
				q.push( make_pair(ny,nx) );
		  }
	 }
  }
  for (int i=0; i < n; ++i){
		printf("%d",d[i][0]);
		for (int j=1; j < m; ++j) printf(" %d",d[i][j]);
		putchar('\n');
  }
}

int main(){
  int runs;
  scanf("%d",&runs);
  while (runs--){
		scanf("%d %d",&n,&m);
		for (int i=0; i < n; ++i) for (int j=0; j < m; ++j) d[i][j] = -1;
		bfs();
  }
  return 0;
}