#include<cstdio>
#include<vector>
#include<queue>
#include<climits>
using namespace std;
int n,s,e;

int f[105];
int d[105];
int t[105][105];

struct node {
  int x,t;
  node(){}
  node(int X,int T){ x = X; t = T; }
  bool operator<(const node &that) const {
	 return t > that.t;
  }
};

void dijkstra(){
  d[s] = 0;
  priority_queue<node> q;
  q.push( node( s , 0 ) );
  int x,w;
  int y,nt;
  while ( !q.empty() ){
	 x = q.top().x;
	 w = q.top().t;
	 q.pop();
	 if ( x == e ) return;
	 if ( d[x] < w ) continue;
	 if ( f[x] && f[x] <= w ) continue;
	 for ( y = 0; y < n; ++y ){
		if ( y != x && t[x][y] ){
		  nt = w + t[x][y];
		  if ( f[x] && nt > f[x] ) continue; //flood while walking
		  if ( f[y] && nt > f[y] ) continue; //Already flooded
		  if ( f[y] && y != e && nt == f[y] ) continue; //special case
		  if ( d[y] > nt ){
			 d[y] = nt;
			 q.push( node(y,nt) );
		  }
		}
	 }
  }
}

int main(){
  int i,j;
  int runs;
  scanf("%d",&runs);
  while (runs--){
	 scanf("%d %d %d",&n,&s,&e);
	 s--,e--;
	 for (i=0; i < n; ++i){
		d[i] = INT_MAX;
		scanf("%d",f+i);
		for (j=0; j < n; ++j){
		  scanf("%d",&t[i][j]);
		}
	 }
	 dijkstra();
	 if ( d[e] < INT_MAX ) printf("%d\n",d[e]);
	 else puts("GENE HACKMAN");
  }
  return 0;
}