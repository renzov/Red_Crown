#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
#define forn(i,n) for( int i=0; i < (int)(n); ++i ) 
int n,m;
int M[8][8];
int sx,sy;
int ex,ey;
int px,py;
bool reach[8][8];
int d[8][8][4];
int dy[]={1,0,-1,0};
int dx[]={0,-1,0,1};
struct state{
  int x,y,z;
  state(){}
  state( int X ,int Y,int Z ){ x = X; y = Y; z = Z; }
};
inline int inv( int z ){ return (z + 2)%4; }
inline bool valid(int nx,int ny){ return !(nx < 0 || nx >= n || ny < 0 || ny >= m || M[nx][ny]); }

void bfs( int xx, int yy , int bx , int by ){
  fill( &reach[0][0] , &reach[n-1][m-1] , false );
  reach[xx][yy] = true;
  queue<state> q;
  q.push( state(xx,yy,0) );
  int x,y,nx,ny;
  while ( !q.empty() ){
	 x = q.front().x; y = q.front().y; q.pop();
	 forn(i,4){
		nx = x + dx[i]; ny = y + dy[i];
		if ( !valid(nx,ny) ) continue;
		if ( bx == nx && by == ny ) continue;
		if ( !reach[nx][ny] ){
		  reach[nx][ny] = true; q.push( state(nx,ny,0) );
		}
 	 }
  }
} 

int main(){
  int res;
  while ( scanf("%d %d",&m,&n) && n && m ){
	 forn(i,n)
		forn(j,m){
		  scanf("%d",&M[i][j]);
		  if ( M[i][j] == 2 ){
			 px = i; py = j; M[i][j] = 0; 
		  }
		  else if ( M[i][j] == 3 ){
			 ex = i; ey = j; M[i][j] = 0; 
		  }
		  else if ( M[i][j] == 4 ){
			 sx = i; sy = j; M[i][j] = 0;
		  }
		}
	 fill( &d[0][0][0] , &d[n-1][m-1][4] , -1 );
	 bfs( sx , sy , px, py );
	 //Init and First Move
	 queue<state> q;
	 int x,y,z;
	 int nx,ny,nz,iz;
	 int prex,prey;
	 res = -1;
	 forn(i,4){
		nx = px + dx[i]; ny = py + dy[i];
		if ( !valid(nx,ny) || !reach[nx][ny] ) continue;
		nz = inv(i);
		if ( d[px][py][nz] == -1 ){
		  q.push( state(px,py,nz) ); d[px][py][nz] = 0;
		}
	 }
	 while ( !q.empty() ){
		x = q.front().x; y = q.front().y; z = q.front().z;
		if ( x == ex && y == ey ){ res = d[x][y][z]; break; }
		q.pop();
		//Move in same direction
		nx = x + dx[z]; ny = y + dy[z];
		if ( valid( nx, ny ) && d[nx][ny][z] == -1 ){
		  q.push( state(nx,ny,z) ); d[nx][ny][z] = d[x][y][z] + 1;
		}
		iz = inv(z); prex = x + dx[iz]; prey = y + dy[iz];
		bfs( prex , prey , x , y );
		forn(i,4){
		  nx = x + dx[i]; ny = y + dy[i];
		  if ( !valid(nx,ny) || !reach[nx][ny] ) continue;
		  nz = inv(i);
		  if ( d[x][y][nz] == -1 ){
			 q.push( state(x,y,nz) ); d[x][y][nz] = d[x][y][z];
		  }
		}
	 }
	 printf("%d\n",res);
  }
  return 0;
}