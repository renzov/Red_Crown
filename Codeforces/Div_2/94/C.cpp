#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int dx[] = {1,1,0,-1,-1,-1,0,1,0};
int dy[] = {0,-1,-1,-1,0,1,1,1,0};
int sx,sy;
int ex,ey;
char M[8][9];

int main(){
  int x,y,nx,ny;

  for (int i=0; i<8; ++i){
	 cin >> M[i];
	 //cout << M[i] << endl;
  }
  sx = 7; sy = 0;
  ex = 0; ey = 7;
  M[sx][sy] = M[ex][ey] = '.';
  bool res = true;
  bool vis[8][8] = {0};

  vector<pair<int,int> > st,next;
  st.push_back( make_pair(sx,sy) );

  for (int h=0; h < 8; ++h){
	 if ( st.empty() ){ res = false; break; }
	 next.clear();
	 for (int i=0; i < st.size(); ++i){
		x = st[i].first;
		y = st[i].second;
		if ( M[x][y] == 'S' ) continue;
		for (int j=0; j < 9; ++j){
		  nx = x + dx[j];
		  ny = y + dy[j];
		  if ( nx < 0 || ny < 0 || nx > 7 || ny > 7 ) continue;
		  if ( M[nx][ny] == 'S' ) continue;
		  if (!vis[nx][ny]){ next.push_back( make_pair( nx,ny ) ); vis[nx][ny] = true; }
		}
	 }
	 if ( vis[ex][ey] ) break;
	 st = next;
	 for (int j=7; j >= 0; --j){
		for (int k=0; k < 8; ++k){
		  vis[j][k] = false;
		  if ( M[j][k] == 'S' ){
			 M[j][k] = '.';
			 if ( j < 7 ) M[j+1][k] = 'S';
		  }
		}
	 }
  }
  if ( st.empty() ) res = false;
  if ( res ) cout << "WIN" << endl;
  else cout << "LOSE" << endl;
  return 0;
}