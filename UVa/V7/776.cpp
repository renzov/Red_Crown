#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<cstdio>
using namespace std;
int r;
int w;
vector< vector<int> > num;
vector< vector<char> > M;

int dx[]={1,1,0,-1,-1,-1,0,1};
int dy[]={0,-1,-1,-1,0,1,1,1};

int size(int n){
  int res = 0;
  while (n){
		res++;
		n/=10;
  }
  return res;
}

void dfs(int y,int x,int n){
  num[y][x] = n;
  int ny,nx;
  for (int i=0; i < 8; ++i){
		nx = x + dx[i];
		ny = y + dy[i];
		if (nx<0 || ny<0 || nx>=w || ny>=r) continue;
		if (num[ny][nx] == -1 && M[ny][nx] == M[y][x])
			 dfs(ny,nx,n);
  }
}

int main(){
  string line;
  char c;
  int runs = 0;
  int t;
  bool fin = false;
  while ( !fin ){
		getline(cin,line);
		runs++;
		num.clear();
		M.clear();
		r = 0;
		do {
		  stringstream in(line);
		  M.push_back( vector<char>() );
		  num.push_back( vector<int>() );
		  while (in >> c){ M.back().push_back(c); num.back().push_back(-1); }
		  if (!getline(cin,line)){ fin = true; break; }
 		}
		while (line != "%" );
		r = M.size();
		w = M[0].size();
		int n = 0;
		for (int i=0; i < r; ++i)
		  for (int j=0; j < w; ++j)
			 if (num[i][j] == -1)
				dfs(i,j,++n);
		vector<int> v(w);
		for (int j=0; j < w; ++j){
		  v[j] = 1;
		  for (int i=0; i < r; ++i){
			 t = size( num[i][j] );
			 if ( t > v[j] ) v[j] = t;
		  }
		}
		for (int i=0; i<r; ++i){
			 for (int j=0; j < w; ++j){
				if (j > 0) putchar(' ');  
				t = size( num[i][j] );
				for (int k=0; k < (v[j] - t); ++k) putchar(' ');
				printf("%d",num[i][j]);
			 }
			 putchar('\n');
		}
		puts("%");
  }
  return 0;
}