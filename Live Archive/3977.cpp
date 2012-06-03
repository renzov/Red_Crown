#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;

struct node{
  int x,y,z;
  node(){}
  node(int X,int Y,int Z){ x = X; y = Y; z = Z; }
  bool operator<(const node &that) const{
	 return z<that.z;
  }
};

int h,w,d;
int H[505][505];
int M[505][505];
int dx[]={0,-1,0,1};
int dy[]={1,0,-1,0};
int cnt;
void dfs( int x , int y , int z ){
  if (H[x][y] == z) cnt++; 
  M[x][y] = z;
  int i;
  int nx,ny;
  for (i=0; i<4; ++i){
	 nx = x + dx[i];
	 ny = y + dy[i];
	 if ( nx < 0 || ny < 0 || nx >= h || ny >= w ) continue;
	 if ( H[nx][ny] > (z-d) ){
		if ( M[nx][ny] == -1 ){
			 dfs( nx, ny , z );
			 M[x][y] = max( M[x][y] , M[nx][ny] );
		}
		else {
		  M[x][y] = max( M[x][y] , M[nx][ny] );
		}
	 }
  }
}

int main(){
  int i,j;
  int x,y;
  int res;
  int runs;

  scanf("%d",&runs);
  while (runs--){
	 scanf("%d %d %d",&h,&w,&d);
	 priority_queue< node > q;
	 for (i=0; i < h; ++i)
		for (j=0; j < w; ++j){
		  scanf("%d",&H[i][j]);
		  M[i][j] = -1;
		  q.push( node(i,j,H[i][j]) );
		}
	 res = 0;
	 while ( !q.empty() ){
		x = q.top().x;
		y = q.top().y;
		q.pop();
		if ( M[x][y] == -1 ){
			cnt = 0;
			dfs( x , y , H[x][y] );
			if ( M[x][y] <= H[x][y] ){ 
			 res += cnt;
			}
		}
	 }
	 printf("%d\n",res);
  }
  return 0;
}