#include<cstdio>
#include<queue>
using namespace std;
int n,m;
int d[55][55];
int M[55][55];
int pred[55][55];
pair<int,int> diff[55][55];
char p[6] = { 'E' , 'N' , 'W' , 'S' , '*' };

bool better( pair<int,int> a, pair<int,int> b){
  if (a.second != b.second) return a.second < b.second;
  return a.first < b.first;
}

int main(){
 
  while (scanf("%d %d",&n,&m) && n){
	 for (int i=0; i < n; ++i)
		for (int j=0; j < m; ++j){
		  scanf("%d",&M[i][j]);
		  pred[i][j] = d[i][j] = -1;
		}
		d[0][0] = 0;
		pred[0][0] = 4;
		queue< pair<int,int> > q;
		q.push( make_pair(0,0) );
		int x,y;
		while (!q.empty()){
		  x = q.front().first;
		  y = q.front().second;
		  q.pop();
		  for (int i=y-1; i >= 0; --i){
			 if ( M[i][x] == (y-i) ){
				  if (d[i][x] == -1){
					 d[i][x] = d[y][x] + 1;
					 pred[i][x] = 3;
					 diff[i][x] = make_pair(x,y);
					 q.push( make_pair(x,i) );
				  }
				  else if ( ( d[i][x] == (d[y][x] + 1) ) && better( make_pair(x,y) , diff[i][x] ) ){
						diff[i][x] = make_pair(x,y);
						pred[i][x] = 3;
				  }
			 }
		  }
		  for (int i=x-1; i >= 0; --i){
			 if (M[y][i] == (x-i)){
				  if (d[y][i] == -1){
					 d[y][i] = d[y][x] + 1;
					 pred[y][i] = 0;
					 diff[y][i] = make_pair(x,y);
					 q.push( make_pair(i,y) );
				  }
				  else if ( ( d[y][i] == (d[y][x] + 1) ) && better( make_pair(x,y) , diff[y][i] ) ){
						diff[y][i] = make_pair(x,y);
						pred[y][i] = 0;
				  }
			 }
		  }
		  for (int i=y+1; i < n; ++i){
			 if (M[i][x] == (i-y)){
				  if (d[i][x] == -1){
					 d[i][x] = d[y][x] + 1;
					 pred[i][x] = 1;
					 diff[i][x] = make_pair(x,y);
					 q.push( make_pair(x,i) );
				  }
				  else if ( ( d[i][x] == (d[y][x] + 1) ) && better( make_pair(x,y) , diff[i][x] ) ){
						diff[i][x] = make_pair(x,y);
						pred[i][x] = 1;
				  }
			 }
		  }
		  for (int i=x+1; i < m; ++i){
			 if (M[y][i] == (i-x)){
				  if (d[y][i] == -1){
					 d[y][i] = d[y][x] + 1;
					 pred[y][i] = 2;
					 diff[y][i] = make_pair(x,y);
					 q.push( make_pair(i,y) );
				  }
				  else if ( ( d[y][i] == (d[y][x] + 1) ) && better( make_pair(x,y) , diff[y][i] ) ){
						diff[y][i] = make_pair(x,y);
						pred[y][i] = 2;
				  }
			 }
		  }
		}
		
		for (int i=0; i < n; ++i){
		  for (int j=0; j < m; ++j){
				if (d[i][j] >= 0){
				  putchar(p[ pred[i][j] ]);
				}
				else {
				  putchar('X');
				}
		  }
		  putchar('\n');
		}
		putchar('\n');
  }
  
  return 0;
}