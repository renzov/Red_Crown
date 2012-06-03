#include<cstdio>
#include<queue>
#include<vector>
#include<climits>
#include<algorithm>
using namespace std;
int dx[]={0,-1,0,1};
int dy[]={1,0,-1,0};

struct node{
  int x,y,w,z;
  node(){};
  node(int X,int Y,int W,int Z){ x = X,y = Y,w = W,z = Z; }
  bool operator<(const node &that) const{ return w >= that.w; }
};

int d[1001][1001][4];
int memo[1001][1001][4];
vector<node> pre[1001][1001][4];
int n,m,mod;
char M[1001][1001];
int sx,sy;
int ey,ex;
int dir;

int get_edge(int a,int b){
   if ( a > b ) return min( a - b, 4 - a + b ) + 1;
	return min( b - a , 4 - b + a ) + 1;
}

int dijsktra(){
  for (int i=0; i < n; ++i)
	 for (int j=0; j < m; ++j){
		  d[i][j][0] = d[i][j][1] = d[i][j][2] = d[i][j][3] = INT_MAX;
		  memo[i][j][0] = memo[i][j][1] = memo[i][j][2] = memo[i][j][3] = -1;
		  pre[i][j][0].clear(); pre[i][j][1].clear();
		  pre[i][j][2].clear(); pre[i][j][3].clear(); 
	 }
  d[ sx ][ sy ][ dir ] = 0;
  priority_queue< node > q;
  q.push( node(sx,sy,0,dir) );
  int x,y,w,z;
  int nx,ny,nw,nz;
  while ( !q.empty() ){
	 x = q.top().x; y = q.top().y; w = q.top().w; z = q.top().z;
	 q.pop();
	 if ( d[x][y][z] > w ) continue;
	 /* move forward */
	 nx = x + dx[z];
	 ny = y + dy[z];
	 nw = w + 1;
	 if ( nx >= 0 && ny >= 0 && nx < n && ny < m && M[nx][ny] == '.' ){
		 if ( d[nx][ny][z] > nw ){
			d[nx][ny][z] = nw; q.push( node( nx , ny , nw , z ) );
			pre[nx][ny][z].clear(); pre[nx][ny][z].push_back( node( x , y , w , z ) );
		}
		else if ( d[nx][ny][z] == nw ){
		   pre[nx][ny][z].push_back( node( x , y , w , z ) );
		}
	 }
	 nz = (z + 1) % 4; //Clockwise
	 if ( d[x][y][nz] > nw ){
			d[x][y][nz] = nw; q.push( node( x , y , nw , nz ) );
			pre[x][y][nz].clear(); pre[x][y][nz].push_back( node( x , y , w , z ) );
	 }
	 else if ( d[x][y][nz] == nw ){
		   pre[x][y][nz].push_back( node( x , y , w , z ) );
	 }
	 nz = (3 + z) % 4; //Clockwise
	 if ( d[x][y][nz] > nw ){
			d[x][y][nz] = nw; q.push( node( x , y , nw , nz ) );
			pre[x][y][nz].clear(); pre[x][y][nz].push_back( node( x , y , w , z ) );
	 }
	 else if ( d[x][y][nz] == nw ){
		   pre[x][y][nz].push_back( node( x , y , w , z ) );
	 }
  }
  return min( d[ex][ey][0] , min(d[ex][ey][1] , min( d[ex][ey][2] , d[ex][ey][3] ) ) );
}

int sum_path( int x , int y , int z ){
  if ( x == sx && y == sy && z == dir ) return 1;
  if ( memo[x][y][z] != -1 ) return memo[x][y][z];
  int res = 0;
  for (int i=0; i < pre[x][y][z].size(); ++i){
	 res += sum_path( pre[x][y][z][i].x , pre[x][y][z][i].y , pre[x][y][z][i].z );
	 res %= mod;
  }
  memo[x][y][z] = res;
  return res;
}

int main(){
  int cases = 0;
  char c;
  int res;
  while ( scanf("%d %d %d",&n,&m,&mod) && mod ){
	 cases++;
	 for (int i=0; i < n; ++i)
		scanf("%s",M[i]);
	 scanf("%d %d %d %d %c",&sx,&sy,&ex,&ey,&c);
	 if ( c == 'E' ) dir = 0;
	 else if ( c == 'N' ) dir = 1;
	 else if ( c == 'W' ) dir = 2;
	 else dir = 3;
	 res = dijsktra();
	 printf("Case %d: ",cases);
	 if ( res >= INT_MAX ) printf("%d -1\n",mod);
	 else {
		printf("%d ",mod);
		int sum = 0;
		for (int i=0; i < 4; ++i){
		  if ( d[ex][ey][i] == res ){
			 sum += sum_path( ex , ey , i );
			 sum %= mod;
		  }
		}
		printf("%d\n",sum);
	 }
  }
  return 0;
}
