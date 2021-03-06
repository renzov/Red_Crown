#include<cstdio>
#include<list>
#include<queue>
using namespace std;
const char WHITE = 0;
const char BLACK = 1;

list< int > G[105];
char color[105];
bool degree[105] = {0};
int m;

int main(){

  int n;
  int v;
  int u;
  
  scanf("%d",&n);
  for (u=0; u < n; ++u){
	 color[u] = -1;
	 while (scanf("%d",&v) && v){
		v--;
		degree[u] = degree[v] = true;
		G[u].push_back(v);
		G[v].push_back(u);
	 }
  }
  
  bool possible = true;
  
  for (int i=0; i < n; ++i)
	 if (!degree[i]){
		possible = false;
		break;  
	 }
  
  if (!possible) puts("0");
  else {
	 m = 0;
	 for (int i=0; i < n; ++i){
		if (color[i]==-1){
		  queue<int> q;
		  q.push(i);
		  color[i] = WHITE;
		  while (!q.empty()){
				u = q.front();
				q.pop();
				if (color[u]==WHITE) m++;
				for (list<int>::iterator it = G[u].begin(); it != G[u].end() ;it++){
				  if (color[*it] == -1){
					 color[*it] = (char)(1-color[u]);
					 q.push(*it);
				  }
				}
		  }
		}
	 }
	 printf("%d\n",m);
	 for (int i=0; i < n; ++i){
		if (color[i]==WHITE){ 
		  printf("%d",i+1); 
		  --m; 
		  if (m) putchar(' '); 
		}
	 }
	 putchar('\n');
  }
  return 0;
}