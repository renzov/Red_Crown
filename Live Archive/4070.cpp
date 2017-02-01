#include<cstdio>
#include<queue>
using namespace std;

int R,C;
char M[32][32];
int d[32][32][32];
int sx,sy;
int m;

struct state{
  int x,y,z;
  state(){}
  state(int X,int Y,int Z){ x = X; y = Y; z = Z; }
};

int dx[]={0,-1,0,1,0};
int dy[]={1,0,-1,0,0};

bool iscar(int x,int y,int z){
  return M[x][(y + z)%m] == '<' || M[x][ (m+y-z)%m ] == '>';
}

int main(){
  int runs;
  bool h;
  char c;
  int i,j,k;
  int x,y,z;
  int nx,ny,nz;
  int res;
  
  scanf("%d",&runs);
  while (runs--){
	 scanf("%d %d",&R,&C);
	 h = false;
	 for (i=0; i<R; ++i)
		for (j=0; j < C; ++j){
			scanf(" %c",&c);
			if ( c == '<' || c == '>' ){
				  h = true;
			}
			else if ( c == '&' ){ sx = i; sy = j; c = '-'; }
			M[i][j] = c;
		}
	 if ( h ) m = C;
	 else m = 1;
	 for (i=0;i<R;++i)
		for (j=0;j<C; ++j)
		  for (k=0; k<m; ++k)
			 d[i][j][k] = -1;
	 d[sx][sy][0] = 0;
	 deque<state> q;
	 q.push_front( state(sx,sy,0) );
	 res = -1;
	 while ( !q.empty() ){
		x  = q.front().x;
		y = q.front().y;
		z = q.front().z;
		q.pop_front();
		nz = (z + 1) % m;
		if ( M[x][y] == '~' ){ res = d[x][y][z]; break; }
		for (i=0; i < 5; ++i){
		  nx = x + dx[i];
		  ny = y + dy[i];
		  if (ny < 0) ny += C;
		  if (ny >= C) ny -= C;
		  if ( nx < 0 || nx >= R ) continue;
		  if ( M[nx][ny] == 'T' ) continue;
		  if ( iscar(nx,ny,nz) ) continue;
		  if ( d[nx][ny][nz] == -1 ){
			 d[nx][ny][nz] = d[x][y][z] + !(M[nx][ny] == '.');
			 if ( !(M[nx][ny] == '.') ) q.push_back( state(nx,ny,nz) );
			 else q.push_front( state(nx,ny,nz) );
		  }
		}
	 }
	 if ( res == -1 ) puts("Impassable");
	 else printf("%d\n",res);
  }
  return 0;
}