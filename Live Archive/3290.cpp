#include<cstdio>
#include<climits>
#include<queue>
using namespace std;

int C[30][30];
int d[30][30][30];
bool p[30][30];
int N,F,T;
int X[8];
int Y[8];

int dx[]={0,-1,0,1,0};
int dy[]={1,0,-1,0,0};
struct node{
  int x,y,z,w;
  node(){}
  node(int X,int Y,int Z,int W){ x = X; y = Y; z = Z; w = W; }
  bool operator<(const node &that) const {
	 return w > that.w;
  }
};

int dijkstra( int sx , int sy ){
  int i,j,k;
  for (i=0; i < N; ++i)
	 for (j=0; j < N;++j)
		for (k=0; k <= T; ++k)
		  d[i][j][k] = INT_MAX;
  d[sx][sy][0] = 0;
  
  priority_queue<node> q;
  q.push( node( sx, sy, 0 , 0 ) );
  int x,y,z,w;
  int nx,ny,nz,nw;

  while (!q.empty()){
	 x = q.top().x;
	 y = q.top().y;
	 z = q.top().z;
	 w = q.top().w;
	 q.pop();
	 if ( d[x][y][z] < w ) continue;
	 nz = z + 1;
	 for (i=0; i < 5; ++i){
		nx = x + dx[i];
		ny = y + dy[i];
		if ( nx < 0 || ny < 0 || nx >= N || ny >= N ) continue;
		nw = w + C[nx][ny];
		if ( d[nx][ny][nz] > nw ){
		  d[nx][ny][nz] = nw;
		  if ( nz < T ) q.push( node( nx, ny , nz, nw ) );
		}
	 }
  }
  int res = 0;
  int t;
  for (i=0; i < F; ++i){
	 t = INT_MAX;
	 for (j=0; j <= T; ++j){
		if ( d[X[i]][Y[i]][j] < t ) t = d[X[i]][Y[i]][j];
	 }
	 if ( t >= INT_MAX ) return INT_MAX;
	 res += t;
  }
  return res;
}

inline int abs(int x){ return x<0? -x:x; }

int main(){
  int i,j,k;
  int res,tmp;
  int bx,by;
  int cases = 0;
  while ( scanf("%d %d %d",&N,&F,&T) && N ){
	 cases++;
	 for (i=0; i < N; ++i)
		for (j=0; j < N; ++j)
		  scanf("%d",&C[i][j]);
	 for (i=0; i < F; ++i){
		scanf("%d %d",X+i,Y+i);
	 }
	 
	 for (i=0; i < N; ++i)
		for (j=0; j < N; ++j){
		  p[i][j] = true;
		  for (k=0; k < F && p[i][j]; ++k){
			 if ( (abs(X[k]-i) + abs(Y[k]-j)) > T ) p[i][j] = false;
		  }
		}
	 res = INT_MAX;
	 for (i=0; i < N; ++i)
		for (j=0; j < N; ++j){
		  if ( p[i][j] ){
			 tmp = dijkstra( i , j );
			 if ( tmp < res ){
				res = tmp;
				bx = i; by = j;
			 } 
		  }
		}
	 printf("Case #%d: ",cases);
	 if ( res < INT_MAX ) printf("Selected city (%d,%d) with minimum cost %d.\n",bx,by,res);
	 else puts("Impossible.");
  }
  return 0;
}