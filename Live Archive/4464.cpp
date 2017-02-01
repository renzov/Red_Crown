#include<cstdio>
#include<queue>
#define forn(i,n) for ( int i=0; i < (int)(n); ++i )
using namespace std;
struct state{
  int x,y,z;
  state(){}
  state(int X,int Y,int Z){ x = X; y = Y; z = Z; }
};
int dy[]={1,0,-1,0};
int dx[]={0,1,0,-1};
char M[1002][1002];
int d[1002][1002][4];
int n,m;
int ex,ey;
int main(){
  int x,y,z;
  int nx,ny,nz;
  while ( scanf("%d %d",&n,&m) && n ){
	 scanf("%d %d",&ey,&ex); ex--,ey--;
	 forn(i,n) scanf("%s",M[i]);
	 if ( M[ex][ey] == '1' || M[0][0] == '1'  ){ puts("NOOO!"); continue; }
	 forn(i,n) forn(j,m) forn(k,4) d[i][j][k] = -1; 
	 queue<state> q;
	 int res = -1;
	 d[0][0][0] = 0;
	 q.push( state(0,0,0) );
	 while ( !q.empty() ){
		x = q.front().x; y = q.front().y; z = q.front().z;
		q.pop();
		if ( ex == x && y == ey ){ res = d[x][y][z]; break; }
		//Moving in same direction
		nx = x + dx[z]; ny = y + dy[z];
		if ( nx >= 0 && ny >= 0 && nx < n && ny < m && M[nx][ny]=='0' ){
		  if ( d[nx][ny][z] == -1 ){
			 d[nx][ny][z] = d[x][y][z] + 1;
			 q.push( state(nx,ny,z) );
		  } 
		}
		// Turning rigth
		nz = (z + 1)%4;
		nx = x + dx[nz]; ny = y + dy[nz];
		if ( nx >= 0 && ny >= 0 && nx < n && ny < m && M[nx][ny]=='0' ){
		  if ( d[nx][ny][nz] == -1 ){
			 d[nx][ny][nz] = d[x][y][z] + 1;
			 q.push( state(nx,ny,nz) );
		  }
		}
 	 }
	 if ( res < 0 ) puts("NOOO!");
	 else printf("%d\n",res);
  }
  return 0;
}