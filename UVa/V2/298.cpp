#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

int n,m;
int d[32][32][7][7];
int sx,sy;
int ex,ey;
bool valid[31][31];

struct node{
  int x,y;
  int vx,vy;
  node(){}
  node(int X,int Y,int Vx,int Vy){ x = X; y = Y; vx = Vx; vy = Vy; }
};

int bfs(){
  if (sx==ex && sy==ey) return 0;
  d[sy][sx][3][3] = 0;
  queue<node> q;
  q.push( node( sx, sy, 0 , 0 ) );
  node tmp;
  int x,y,vx,vy;
  int nx,ny,nvx,nvy;
  bool finish = false;
  int res;
  while ( !q.empty() && !finish ){
	 tmp = q.front();
	 q.pop();
	 x = tmp.x; y = tmp.y;
	 vx = tmp.vx; vy = tmp.vy;
	 for (int k=-1; k <= 1 && !finish; ++k)
		 for (int l=-1; l <= 1 && !finish; ++l){
			 nvx = vx + k; nvy = vy + l;
			 if (nvx < -3 || nvx > 3 || nvy < -3 || nvy > 3) continue;
			 nx = x + nvx; ny = y + nvy;
			 if (nx<0||ny<0||nx>=m||ny>=n) continue;
			 if (!valid[ny][nx]) continue;
			 if ( d[ny][nx][nvy+3][nvx+3] == -1){
				d[ ny ][ nx ][ nvy + 3 ][ nvx + 3 ] = d[y][x][vy+3][vx+3] + 1;
				if ( ny == ey && nx == ex ){ res = d[ ny ][ nx ][ nvy + 3 ][ nvx + 3 ]; finish = true; }
				q.push( node(nx,ny,nvx,nvy) );
			 }
		  }
  }
  if (finish) return res;
  return -1;
}

int main(){
  int runs;
  int x[2];
  int y[2];
  int p;
  scanf("%d",&runs);
  while (runs--){
	 scanf("%d %d",&m,&n);
	 scanf("%d %d",&sx,&sy);
	 scanf("%d %d",&ex,&ey);
	 for (int i=0; i < n; ++i)
		for (int j=0; j < m; ++j){
		  valid[i][j] = true;
		}
	 memset(d,-1,sizeof(d));
	 scanf("%d",&p);
	 while (p--){
		scanf("%d %d %d %d",x,x+1,y,y+1);
		for (int i=y[0]; i <= y[1]; ++i)
		  for (int j=x[0]; j <= x[1] ; ++j)
			 valid[i][j] = false;
	 }
	 int res = bfs();
	 if (res < 0) puts("No solution.");
	 else printf("Optimal solution takes %d hops.\n",res);
  }
  return 0;
}