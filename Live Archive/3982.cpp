#include<cstdio>
#include<string>
#include<map>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;

int n,m;
int ex,ey;
int nr;

struct node{
  int x,y;
  node(){}
  node(int X,int Y){ x = X; y = Y; }
};

int d[1005][1005];

int main(){
  int runs;
  int e;
  char name[10];
  int u,v,t;
  int x,y;
  string edge;
  int i,j;
  vector<int> tmp;
  scanf("%d",&runs);
  while (runs--){
	 scanf("%d",&n);
	 scanf("%d",&ex);
	 scanf("%d",&e);
	 map<string,int> hash;
	 vector< vector<node> > G(n);
	 nr = 0;
	 while (e--){
		scanf("%d %s %d",&u,name,&v);
		edge = string(name);
		if ( hash.find(edge) == hash.end() ){ hash[edge] = nr++; }
		t = hash[edge];
		G[u].push_back(node(v,t));
	 }
	 scanf("%d",&m);
	 scanf("%d",&ey);
	 scanf("%d",&e);
	 vector< map< int, vector<int> > > L(m);
	 while (e--){
		scanf("%d %s %d",&u,name,&v);
		edge = string(name);
		if ( hash.find(edge) == hash.end() ){ hash[edge] = nr++; }
		t = hash[edge];
		L[u][t].push_back(v);
	 }
	 for (i=0; i < n; ++i) for (j=0; j<m; ++j) d[i][j] = -1;
	 queue<node> q;
	 q.push(node(0,0));
	 d[0][0] = 0;
	 while (!q.empty()){
		x = q.front().x;
		y = q.front().y;
		q.pop();
		if ( ex == x && ey == y ) break;
		for (i=0; i < G[x].size(); ++i){
		  u = G[x][i].x;
		  t = G[x][i].y;
		  if ( L[y][t].size() ){
			 tmp = L[y][t];
			 for (j=0; j < tmp.size() ; ++j){
				v = tmp[j];
				if ( d[u][v] == -1 ){
				  d[u][v] = d[x][y] + 1;
				  q.push(node(u,v));
				}
			 }
		  }
		}
	 }
	 printf("%d\n",d[ex][ey]);
	 if (runs) putchar('\n');
  }

  return 0;
}