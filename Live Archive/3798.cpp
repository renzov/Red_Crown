#include<cstdio>
#include<cstring>
#include<queue>
#include<cctype>
using namespace std;
const int INF = 9999999;
char M[105][105];
int d[105][105][30];
int dx[]={0,-1,0,1};
int dy[]={1,0,-1,0};
int n,m;

struct node{
  int x,y,s,t;
  bool operator<( const node &that ) const {
	 return t > that.t;
  }
  node(){}
  node(int X,int Y,int S,int T){ x = X; y = Y; s = S; t = T; }
};

int main(){
  int i,j,k;
  int res;
  bool found;
  while (1){
	 gets( M[0] );
	 if ( M[0][0] == '-' ) break;
	 n = 1;
	 while (gets(M[n]) && M[n][0]){
		n++;
	 }
	 m = strlen(M[0]);
	 /* Dijkstra */
	 priority_queue< node > q;
	 
	 for (i=0; i < n; ++i)
		 for (j=0; j < m; ++j)
			for (k=0; k < 27; ++k)
				 d[i][j][k] = INF;
	 
	 for (i=0; i < m; ++i){
		if ( M[0][i] != '*' ){
		  if ( isalpha( M[0][i] ) ){ d[0][i][M[0][i]-'A' + 1] = 0; q.push( node(0,i,M[0][i]-'A' + 1,0) ); }
		  else { q.push( node(0,i,0,0) ); d[0][i][0] = 0; }
		}
		if ( M[n-1][i] != '*' ){
		  if ( isalpha( M[n-1][i] ) ){ d[n-1][i][M[n-1][i]-'A' + 1] = 0; q.push( node(n-1,i,M[n-1][i]-'A' + 1,0) ); }
		  else { q.push( node(n-1,i,0,0) ); d[n-1][i][0] = 0; }
		}
		M[0][i] = M[n-1][i] = '*';
	 }
	 for (i=0; i < n; ++i){
		if ( M[i][0] != '*' ){
		  if ( isalpha( M[i][0] ) ){ d[i][0][M[i][0]-'A' + 1] = 0; q.push( node(i,0,M[i][0]-'A' + 1,0) ); }
		  else { q.push( node(i,0,0,0) ); d[i][0][0] = 0; }
		}
		if ( M[i][m-1] != '*' ){
		  if ( isalpha( M[i][m-1] ) ){ d[i][m-1][M[i][m-1]-'A' + 1] = 0; q.push( node(i,m-1,M[i][m-1]-'A' + 1,0) ); }
		  else { q.push( node(i,m-1,0,0) ); d[i][m-1][0] = 0; }
		}
		M[i][m-1] = M[i][0] = '*';
	 }
	 found = false;
	 node top;
	 int x,y,t,s,l;
	 int nx,ny;
	 int nt,ns;
	 
	 while (!q.empty()){
		 top = q.top(); q.pop();
		 x = top.x; y = top.y; t = top.t; s = top.s;
		 if ( M[x][y] == '$'){ res = t; found = true; break;}
		 if ( d[x][y][s] < t ) continue;
		 for (i=0; i < 4; ++i){
			 nx = x + dx[i]; ny = y + dy[i];
			 if ( nx < 0 || ny < 0 || ny >= m || nx >= n) continue;
			 if ( M[nx][ny] == '.' || M[nx][ny] == '$' ){
				  if ( d[nx][ny][s] > d[x][y][s] ){ d[nx][ny][s] = d[x][y][s]; q.push( node(nx,ny,s,d[x][y][s]) );  }
			 }
			 if ( isdigit(M[nx][ny]) ){
				l = M[nx][ny] - '0';
				if ( d[nx][ny][s] > (d[x][y][s] + l) ){ d[nx][ny][s] = d[x][y][s] + l; q.push( node(nx,ny,s,d[x][y][s] + l) ); }
				if ( s > 0 && ( d[nx][ny][s-1] > d[x][y][s] ) ){ d[nx][ny][s-1] = d[x][y][s]; q.push( node(nx,ny,s-1,d[x][y][s]) ); }
			 }
		 }
	 }
	 if ( !found ) puts("IMPOSSIBLE");
	 else printf("%d\n",res);
  }
  return 0;
}