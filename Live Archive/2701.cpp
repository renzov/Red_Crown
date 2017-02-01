#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

int pred[205];
int d[205];
int mov[205];
int n;

void bfs(){
  queue<int> q;
  q.push(1);
  mov[1 % n] = 1;
  d[ 1 % n ] = 0;
  int u,v;
  while (!q.empty()){
	 u = q.front();
	 q.pop();
	 if ( u == 0 ) break;
	 v = ( u * 10 ) % n;
	 if (d[v] == -1){ d[v] = d[u] + 1; pred[v] = u; mov[v] = 0; q.push(v); }
	 if (v==0) return;
	 v = (u*10 + 1) % n;
	 if (d[v] == -1){ d[v] = d[u] + 1; pred[v] = u; mov[v] = 1; q.push(v); }
	 if (v==0) return;
  }
}

void print_path(int u){
  if ( pred[u] != -1 ){
	 print_path( pred[u] );
	 printf("%d",mov[u]);
  }
  else {
	 printf("%d",mov[u]);
  }
}

int main(){
  int i;
  while (scanf("%d",&n) && n){
	 for(i=0; i < n; ++i) pred[i] = d[i] = -1;
	 bfs();
	 print_path(0);
	 putchar('\n');
  } 
  return 0;
}