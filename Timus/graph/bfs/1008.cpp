#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include<algorithm>
#include<sstream>
#include<set>
using namespace std;

int n;
char M[15][15] = {0};
int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};
int d[15][15];
set< pair<int,int> > S;

void printSecond(){
  int x,y;
  int nx,ny; 
  vector< pair<int,int> > p(n);

  for (int i=1; i <= 10; ++i)
	 for(int j=1; j <= 10; ++j)
		d[i][j] = -1;

  for (int i=0; i < n; ++i){
	 cin >> p[i].first >> p[i].second;
	 M[ p[i].first ][ p[i].second ] = 1;
  }
  sort( p.begin() , p.end() );
  int left = n;
  queue< pair<int,int> > q;
  cout << p[0].first << " " << p[0].second << endl;
  for (int i=0; i < n; ++i){
	 if (d[ p[i].first ][ p[i].second ] == -1){
		q.push( make_pair( p[i].first , p[i].second ) );
		d[ p[i].first ][ p[i].second ] = 0;
		while (!q.empty()){
		  x = q.front().first;
		  y = q.front().second;
		  q.pop();
		  for (int i=0; i < 4; ++i){
			 ny = y + dy[i];
			 nx = x + dx[i];
			 if (x < 1 || y < 1 || x > 10 || y > 10) continue;
			 if (M[nx][ny] && d[nx][ny] == -1){
				switch( i ){
				  case 0 : cout << 'R'; break;
				  case 1 : cout << 'T'; break;
				  case 2 : cout << 'L'; break;
				  case 3 : cout << 'B'; break;
				}
				d[nx][ny] = d[x][y] + 1;
				q.push( make_pair(nx,ny) );
			 }
		  }
		  left--;
		  if (left) cout << ',' << endl;
		  else cout << '.' << endl;
		}
	 }
	 
  }
}

void printFirst(int x,int y){
  queue< pair<int,int> > q;
  q.push( make_pair(x,y) );
  string line;
  while (!q.empty()){
	 x = q.front().first;
	 y = q.front().second;
	 S.insert( make_pair(x,y) );
	 q.pop();
	 getline(cin,line);
	 for (int i=0; i < line.size()-1; ++i){
		switch(line[i]){
		  case 'R': q.push( make_pair(x+dx[0],y+dy[0]) ); break;
		  case 'T': q.push( make_pair(x+dx[1],y+dy[1]) ); break;
		  case 'L': q.push( make_pair(x+dx[2],y+dy[2]) ); break;
		  case 'B': q.push( make_pair(x+dx[3],y+dy[3]) ); break;	 
		}
		
	 }
  }
  cout << S.size() << endl;
  for (set< pair<int,int> >::iterator it = S.begin(); it != S.end() ; it++)
	 cout << it->first << " " << it->second << endl;
  
}

int main(){
  int x,y;
  string line;
  
  getline(cin,line);
  stringstream in(line);
  in >> x;
  if ( in >> y ){
	 printFirst(x,y);
  }
  else {
	 n = x;
	 printSecond();
  }
  return 0;
}