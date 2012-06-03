#include<queue>
#include<cstdio>

using namespace std;

int dx[]={1,0,-1,0};
int dy[]={0,-1,0,1};
char visited[50][50]={ 0 };
int main(){

  
  char M[50][50];
  int n;
  scanf("%d",&n);
  for (int i=1; i <= n; ++i)
	 scanf("%s",&M[i][1]);
  for (int i=0; i <= n + 1; ++i){
	 M[0][i] = '#';
	 M[n+1][i] = '#';
	 M[i][0] = '#';
	 M[i][n+1] = '#';
  }
  M[0][1] = M[1][0] = M[n][n+1] = M[n+1][n] = '*';
  queue< pair<int,int> > q;
  q.push( make_pair( 1,1 ) );
  q.push( make_pair( n,n ) );
  visited[1][1] = 1;
  visited[n][n] = 1;
  int x,y;
  int nx,ny;
  int res = 0;
  while (!q.empty()){
		x = q.front().first;
		y = q.front().second;
		q.pop();
		for (int i=0; i < 4; ++i){
		  nx = x + dx[i];
		  ny = y + dy[i];
		  if (M[ny][nx] == '.' && !visited[ny][nx]){
			 visited[ny][nx] = 1;
			 q.push( make_pair(nx,ny) );
		  }
		  else if (M[ny][nx] == '#') res++;
		}
  }
  printf("%d\n",res*9);
  return 0;
}