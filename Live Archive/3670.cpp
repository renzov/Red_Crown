#include<cstdio>
#include<queue>
using namespace std;

int M[25][25];
int d[25][25][25];

struct triple{
  int x,y,z;
  triple(){}
  triple(int X,int Y,int Z){ x = X; y = Y; z = Z; }
};

int dx[]={0,-1,0,1};
int dy[]={1,0,-1,0};

int main(){
  int n,m,t;
  int runs;
  int i,j,k;
  int res;
  int x,y,z;
  int nx,ny;
  scanf("%d",&runs);
  while (runs--){
	 scanf("%d %d",&n,&m);
	 scanf("%d",&t);
	 for (i=0; i<n; ++i)
		for (j=0; j < m ;++j)
		  scanf("%d",&M[i][j]);
	 for (i=0; i<n; ++i)
		for (j=0; j < m; ++j)
		  for (k=0; k <= t; ++k)
			 d[i][j][k] = -1;
	 queue<triple> q;
	 d[0][0][0] = 0;
	 q.push( triple(0,0,0) );
	 res = -1;
	 while (!q.empty()){
		x = q.front().x;
		y = q.front().y;
		z = q.front().z;
		q.pop();
		if ( x==(n-1) && y==(m-1) ){ res = d[x][y][z]; break; }
		for (i=0; i < 4; ++i){
			 nx = x + dx[i];
			 ny = y + dy[i];
			 if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
			 if ( M[nx][ny] ){
				if ( (z + 1) <= t && d[nx][ny][z+1] == -1 ){
				  q.push( triple(nx,ny,z+1) );
				  d[nx][ny][z+1] = d[x][y][z] + 1;
				}
			 }
			 else if (d[nx][ny][0] == -1) {
				  q.push( triple(nx,ny,0) );
				  d[nx][ny][0] = d[x][y][z] + 1;
			 }
		}
	 }
	 printf("%d\n",res);
  }
  return 0;
}