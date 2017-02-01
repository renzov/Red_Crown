#include<cstdio>
#include<queue>
#include<cstring>

using namespace std;
int coin[45][2];
int d[305][305];
int main(){
  int runs;
  int e;
  int n;
  int x,y;
  int nx,ny;

  scanf("%d",&runs);
  while (runs--){
	 scanf("%d %d",&n,&e);
	 for (int i=0; i<n; ++i) scanf("%d %d",&coin[i][0],&coin[i][1]);
	 queue< pair<int,int> > q;
	 for (int i=0; i <= e; ++i)
		for (int j=0; j <= e; ++j)
			 d[i][j] = -1;
	 for (int i=0; i <= e; ++i){
		for (int j=0; j <= e; ++j){
				if ((i*i + j*j) > e*e) break;
				if ((i*i + j*j) == e*e){
				  q.push( make_pair(i,j) );
				  d[i][j] = 0;
				}
		}
	 }
	
	 while (!q.empty()){
		  x = q.front().first;
		  y = q.front().second;
		  q.pop();
		  if (x==0 && y == 0) break;
		  for (int i=0; i < n; ++i){
			 ny = y - coin[i][1];
			 nx = x - coin[i][0];
			 if (nx < 0 || ny < 0) continue;
			 if (d[nx][ny] == -1){
				  d[nx][ny] = d[x][y] + 1;
				  q.push( make_pair(nx,ny) );
			 }
		  }
	 }
	 if (d[0][0] == -1) printf("not possible\n");
	 else printf("%d\n",d[0][0]);
  }
  return 0;
}