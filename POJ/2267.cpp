#include<cstdio>
#include<string>
#include<map>
#include<vector>
#include<queue>
using namespace std;
const int INF = 9999999;

struct node {
  int x,t;
  node(){}
  node(int X,int T){ x = X; t = T; }
};

struct triple{
  int x,t,d;
  triple(){}
  triple(int X,int T,int D){ x = X; t = T; d = D; }
};

int n = 0;
vector<node> G[101][24];
int d[101][24];

int bfs(int s,int e){
  for (int i=0; i < n; ++i)
	 for (int j=0; j < 24; ++j)
		d[i][j] = INF;
  deque< triple > q;
  d[s][18] = 0;
  q.push_front( triple( s , 18 , 0 ) );
  triple top;
  int u,v,t,dist;
  int nt;
  while ( !q.empty() ){
	 top = q.front();
	 q.pop_front();
	 u = top.x;
	 t = top.t;
	 dist = top.d;
	 if ( dist > d[u][t] ) continue;
	 if (u==e) return dist;
	 for (int i=0; i < G[u][t].size(); ++i){
		v = G[u][t][i].x;
		nt = G[u][t][i].t;
		if ( d[v][nt] > d[u][t] ){ 
		  d[v][nt] = d[u][t]; 
		  q.push_front( triple(v,nt,d[v][nt] ) ); 
		}
	 }
	 /* Siempre te puedes quedar */
	 nt = (t + 1) % 24;
	 v = u;
	 if ( t == 12 ){
		  if ( d[v][nt] > (d[u][t] + 1) ){ 
			 d[v][nt] = d[u][t] + 1; 
			 q.push_back( triple(v,nt,d[v][nt] ) ); 
		  }
	 }
	 else {
		if ( d[v][nt] > d[u][t] ){ 
		  d[v][nt] = d[u][t]; 
		  q.push_front( triple(v,nt,d[v][nt] ) ); 
		}
	 }
  }
  return INF;
}

int main(){
  int runs;
  int m;
  int u,v;
  char from[30];
  char to[30];
  int start,len,end;
  string a,b;
  scanf("%d",&runs);
  for (int k=1; k <= runs; ++k){

	 for (int i=0; i < n; ++i)
		for (int j=0; j < 24; ++j)
		  G[i][j].clear();

	 map<string,int> hash;

	 scanf("%d",&m);
	 n = 0;

	 for (int i=0; i < m; ++i){
		scanf("%s %s %d %d",from,to,&start,&len);
		a = string(from);
		b = string(to);
		if ( hash.find(a) == hash.end() ){ hash[a] = n++; }
		if ( hash.find(b) == hash.end() ){ hash[b] = n++; }
		u = hash[a]; v = hash[b];
		start %= 24;
		if (len > 12) continue;
		if ( start >= 6 && start < 18 ) continue;
		end = (start + len) % 24;
		if ( end > 6 && end < 18 ) continue;
		G[u][start].push_back( node(v,end) );
	 }

	 scanf("%s %s",from,to);
	 a = string(from);
	 b = string(to);

	 printf("Test Case %d.\n",k);
	 if ( hash.find(a) == hash.end() || hash.find(b) == hash.end() ){ 
		puts("There is no route Vladimir can take."); 
		continue;
	 }
	 int res = bfs( hash[a] , hash[b] );
	 if (res >= INF) puts("There is no route Vladimir can take.");
	 else printf("Vladimir needs %d litre(s) of blood.\n",res);

  }
  return 0;
}