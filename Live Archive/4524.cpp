#include<cstdio>
#include<climits>
#include<vector>
#include<climits>
#include<queue>
using namespace std;

vector<int> G[26];
vector<int> C[26];
int pred[26][26];
int d[26][26];
int s;
struct node{
  int u,l,w;
  node(){}
  node(int x,int y,int z){ u = x; l = y; w = z; }
  bool operator<(const node &that) const {
	 return w > that.w;
  }
};

int dijkstra(int st,int e){
  int i,j;
  int u,v,l,w;
  for (i=0; i < 26; ++i)
	 for (j=0; j < s; ++j){
		pred[i][j] = -1;
		d[i][j] = INT_MAX;
	 }
  d[st][0] = 0;
  priority_queue<node> q;
  q.push( node( st , 0 , 0 ) );
  while ( !q.empty() ){
	 u = q.top().u;
	 w = q.top().w;
	 l = q.top().l;
	 q.pop();
	 if ( d[u][l] < w ) continue;
	 if ( u==e ) continue; 
	 for (i=0; i < G[u].size(); ++i){
		v = G[u][i];
		if ( d[v][l+1] > ( w + C[u][i] ) ){
		  d[v][l+1] = w + C[u][i];
		  pred[v][l+1] = u;
		  if ( (l+1) < (s-1) ){
			 q.push( node( v , l+1 , d[v][l+1] ) );
		  }
		}
	 }
  }
  w = INT_MAX;
  for (i=0; i < s; ++i)
	  if ( w > d[e][i] ) w = d[e][i];
  return w;
}

void print_path(int u,int v,int l){
  if ( u==v ){
	 printf("%c",(char)('A'+u));
	 return;
  }
  print_path( u , pred[v][l] , l-1 );
  printf(" %c",(char)('A'+v));
}

int main(){
  int m;
  int i,j;
  char a,b;
  int u,v,w;
  int q;
  scanf("%d %d",&s,&m);
  for (i=0; i < m; ++i){
	 scanf(" %c %c %d\n",&a,&b,&w);
	 u = a - 'A';
	 v = b - 'A';
	 G[u].push_back(v);
	 C[u].push_back(w);
	 G[v].push_back(u);
	 C[v].push_back(w);
  }
  scanf("%d",&q);
  for (i=0; i < q; ++i){
	 scanf(" %c %c",&a,&b);
	 u = a - 'A';
	 v = b - 'A';
	 w = dijkstra(u,v);
	 for (j=0; j < s; ++j){
		 if ( d[v][j] == w ){
			 print_path(u,v,j);
			 putchar('\n');
			 break;
		 }
	 }
  }
  return 0;
}