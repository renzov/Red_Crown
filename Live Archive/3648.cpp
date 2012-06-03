#include<string>
#include<queue>
#include<iostream>
#include<cctype>
using namespace std;

struct node{
  int x,y,z;
  node(){}
  node(int X,int Y,int Z){ x = X; y = Y; z = Z; }
};

int n,m;
int sx,sy;
int ex,ey;
int pre[256];
int dx[]={1,0,-1,0};
int dy[]={0,-1,0,1};

int main(){
  string s;
  while ( cin >> s ){
	 cin >> m >> n;
	 vector< vector<char> > M( n , vector<char>(m) );
	 for (int i=0; i < n; ++i)
		for (int j=0; j < m; ++j)
		  cin >> M[i][j];
	 for (int i=0; i<26; ++i) pre[ s[i] ] = i + 1;
	 vector< vector< vector<int> > > d( n, vector< vector<int> >( m , vector<int> ( 27 , -1 ) ) );
	 cin >> sx >> sy;
	 cin >> ex >> ey;
	 if ( M[sy][sx] == 'x' || M[ey][ex] == 'x' ){
		cout << "IMPOSSIBLE" << endl;
		continue;
	 }
	 int x,y,z;
	 int res;
	 int nx,ny,nz;
	 if ( M[sy][sx] >= 'A' && M[sy][sx] <= 'Z' ) z = pre[ M[sy][sx] ];
	 else z = 0;
	 d[sy][sx][z] = 0;
	 queue< node > q;
	 q.push( node( sx , sy , z ) );
	 res = -1;
	 while ( !q.empty() ){
		x = q.front().x;	y = q.front().y;	z = q.front().z;
		q.pop();
		if ( x == ex && y == ey ){ res = d[y][x][z]; break; }
		for (int i=0; i < 4; ++i){
		  nx = x + dx[i];
		  ny = y + dy[i];
		  if ( nx < 0 || ny < 0 || nx >= m || ny >= n ) continue;
		  if (M[ny][nx]=='x') continue;
		  if ( M[ny][nx] == 'o' ){
			 if ( d[ny][nx][z] == -1 ){  
				d[ny][nx][z] = d[y][x][z] + 1;
				q.push( node(nx,ny,z) );
			 }
		  }
		  else if ( pre[M[ny][nx]] > z ){
				nz = pre[M[ny][nx]];
				if ( d[ny][nx][nz] == -1 ){
				  d[ny][nx][nz] = d[y][x][z] + 1;
				  q.push( node(nx,ny,nz) );
				}
		  }
		}
	 }
	 if ( res != -1 ) cout << res << endl;
	 else cout << "IMPOSSIBLE" << endl;
  }
  return 0;
}