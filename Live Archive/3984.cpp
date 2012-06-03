#include<cstdio>
#include<queue>
using namespace std;

struct Magic {
  int x,y,w,t;
};
struct state{
  int x,y,idx,t;
  state(){}
  state(int X,int Y,int I,int T){
	 x = X; y = Y; idx = I; t = T;
  }
};

Magic F[5000];
int M[300][300];
int mag[300][300];
int R,C;
int n;
int d[300][300];
int f[5000][11][11][6];
int dx[]={1,0,-1,0};
int dy[]={0,-1,0,1};
int sy,sx,ey,ex;

inline bool valid( int x ,int y ){
  return x >= 0 && x < C && y >= 0 && y < R && ( M[y][x] != 0 );
}

void init(){
  int i,j,l,k;
  for ( int i=0;i < R; ++i )
	 for ( int j=0; j < C; ++j )
		d[i][j] = -1;
  for ( i=0; i < n; ++i )
	 for ( j=0; j < 11; ++j )
		for ( k=0; k < 11; ++k )
		  for ( l=0; l < 6; ++l )
			 f[i][j][k][l] = -1;
}

int bfs(){
  int x,y,t,z,idx,nx,ny;
  int xr,yr,nxr,nyr,nt,ni;
  queue<state> q;
  if ( mag[sy][sx] == -1){
	 d[sy][sx] = 0;
	 q.push( state( sx , sy , -1, 0 ) );
  }
  else {
	 idx = mag[sy][sx];
	 t = F[idx].t;
	 f[ idx ][ t ][ t ][ t ] = 0;
	 q.push( state( t , t , idx , t ) );
  }
  while ( !q.empty() ){
	 x = q.front().x; y = q.front().y; idx = q.front().idx; t = q.front().t;
	 q.pop();
	 if ( idx == -1 ){
		xr = x; yr = y;
	 }
	 else {
		xr = ( x - F[idx].t )*F[idx].w + F[idx].x; yr = ( y - F[idx].t )*F[idx].w + F[idx].y;
	 }
	 if ( xr == ex && yr == ey ) return ( idx == -1 )? d[yr][xr]:f[idx][y][x][t];
	 if ( idx == -1 ){
		for ( int i=0; i < 4; ++i ){
		  nx = xr + dx[i];
		  ny = yr + dy[i];
		  if ( valid( nx, ny ) ){
			 if ( mag[ny][nx] == -1 ){
				if ( d[ny][nx] == -1 ){ d[ny][nx] = d[y][x] + 1; q.push( state(nx,ny,-1,0) ); }
			 }
			 else {
				idx = mag[ny][nx]; t = F[idx].t;
				if ( f[idx][t][t][t] == -1 ){
				  f[idx][t][t][t] = d[y][x] + 1; q.push( state( t ,t , idx , t ) );
				}
			 }
		  }
		}
	 }
	 else {
		z = f[idx][y][x][t];
		for ( int i=0; i < 4; ++i ){
		  nxr = xr + dx[i]*F[idx].w;  nx = x + dx[i];
		  nyr = yr + dy[i]*F[idx].w;  ny = y + dy[i];
		  if ( valid( nxr , nyr ) ){
			 if ( t == 1 ){
				if ( mag[nyr][nxr] == -1 && d[nyr][nxr] == -1 ){
				  d[nyr][nxr] = z + 1; q.push( state(nxr,nyr,-1,0) );
				}
				else if ( mag[nyr][nxr] != -1 ){
				  ni = mag[nyr][nxr]; nt = F[ni].t;
				  if ( f[ni][nt][nt][nt] == -1){ f[ni][nt][nt][nt] = z + 1; q.push( state(nt,nt,ni,nt) ); }
				}
			 }
			 else {
				if ( mag[nyr][nxr] == -1 || mag[nyr][nxr] == idx ){
				  if ( f[idx][ny][nx][t-1] == -1 ){
					 f[idx][ny][nx][t-1] = z + 1; q.push( state(nx,ny,idx,t-1) );
				  }
				}
				else {
				  ni = mag[nyr][nxr]; nt = F[ni].t;
				  if ( f[ni][nt][nt][nt] == -1 ){
					 f[ni][nt][nt][nt] = z + 1; q.push( state( nt , nt , ni , nt ) );
				  }
				}
			 }
		  }
		}
	 }
  }
  return -1;
}

int main(){
  int runs;
  int res;
  scanf("%d",&runs);
  while ( runs-- ){
	 scanf("%d %d",&R,&C);
	 n = 0;
	 for ( int i=0; i < R; ++i )
		for ( int j=0; j < C; ++j ){
		  scanf("%d",&M[i][j]);
		  if ( M[i][j] < 10 ){
			 mag[i][j] = -1;
		  }
		  else {
			 mag[i][j] = n;
			 F[n].x = j; F[n].y = i;
			 F[n].w = M[i][j] % 10; F[n].t = M[i][j] / 10;
			 n++;
		  }
		}
	 scanf("%d %d",&sy,&sx);
	 scanf("%d %d",&ey,&ex);
	 if ( M[sy][sx] == 0 ) puts("IMPOSSIBLE");
	 else {
		init();
		res = bfs();
		if ( res < 0 ) puts("IMPOSSIBLE");
		else printf("%d\n",res);
	 }
	 if ( runs ) putchar('\n');
  }
  return 0;
}