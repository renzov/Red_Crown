#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
int L,H,W,N,S;
char M[101][101][102];
int d[101][101][102];
int sz,sy,sx;
int X[101];
int Y[101];
int Z[101];
int P[101];
int dx[]={1,0,-1,0};
int dy[]={0,-1,0,1};
int dp[10005];

struct triple{
  int x,y,z;
  triple(){}
  triple(int xx,int yy,int zz){ x=xx; y=yy; z=zz; }
};

void bfs(){
  int x,y,z,i;
  int nx,ny;
  d[sz][sy][sx] = 0;
  queue<triple> q;
  q.push( triple(sx,sy,sz) );
  while ( !q.empty() ){
	 x = q.front().x; y = q.front().y; z = q.front().z;
	 q.pop();
	 for ( i=0; i < 4; ++i ){
		nx = x + dx[i]; ny = y + dy[i];
		if ( nx < 0 || ny < 0 || ny >= H || nx >= W || M[z][ny][nx] == 'X' ) continue;
		if ( d[z][ny][nx] == -1 ){
		  d[z][ny][nx] = d[z][y][x] + 1;
		  q.push( triple(nx,ny,z) );
		}
	 }
	 if ( M[z][y][x] == 'U' && (z+1)<L && d[z+1][y][x] == -1 ){
		d[z+1][y][x] = d[z][y][x] + 1;
		q.push( triple(x,y,z+1) );
	 }
	 if ( M[z][y][x] == 'D' && z>0 && d[z-1][y][x] == -1 ){
		d[z-1][y][x] = d[z][y][x] + 1;
		q.push( triple(x,y,z-1) );
	 }
  }
}

int main(){
  int i,j,k;
  int runs;
  int x,y,z;
  scanf("%d",&runs);
  while ( runs-- ){
	 scanf("%d %d %d %d %d",&L,&H,&W,&N,&S);
	 for ( i=0; i < L; ++i ){
		for ( j=0; j < H; ++j ){
		  scanf("%s",M[i][j]);
		  for ( k=0; k < W; ++k ){
			 d[i][j][k] = -1;
			 if ( M[i][j][k] == 'S' ){ sz = i; sy = j; sx = k; }
		  }
		}
	 }
	 for ( i=0; i < N; ++i ){
		scanf("%d %d %d %d",Z+i,Y+i,X+i,P+i);
		X[i]--,Y[i]--,Z[i]--;
	 }
	 bfs();
	 for ( i=0; i <= S; ++i ) dp[i] = 0;
	 for ( i=0; i < N; ++i ){
		x = X[i]; y = Y[i]; z = Z[i];
		if ( d[ z ][ y ][ x ] != -1 ){
		  for ( j=S; j >= (3*d[z][y][x]) && j > 0 ; --j ){
				dp[j]= max( dp[j] , dp[ j - 3*d[z][y][x] ] + P[i] );
		  }
		}
	 }
	 printf("%d\n",dp[S]);
  }
  return 0;
}