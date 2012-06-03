#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;

int pred[5005];
int mov[5005];
bool visited[5005];
bool digit[10];
int m;

void print_path( int x ){
	if ( pred[x] == -1 ){
		printf("%d",mov[x]);
	}
	else {
		print_path( pred[x] );
		printf("%d",mov[x]);
	}
}

void bfs(){
  queue<int> q;
  for (int i=1; i < 10; ++i){
		if ( digit[i] && !visited[ i % m ] ){
		  visited[ i % m ] = true;
		  mov[ i % m ] = i;
		  q.push( i % m );
		}
  }
  if (visited[0]) return;
  int u,v;
  while (!q.empty()){
	 u = q.front();
	 q.pop();
	 for (int i=0; i < 10; ++i){
		if (digit[i]){
		  v = (u * 10 + i)%m;
		  if ( !visited[v] ){
			 visited[v] = true;
			 mov[v] = i;
			 pred[v] = u;
			 if (v==0) return;
			 q.push(v);
		  }
		}
	 }
  }
}

int main(){
  int n;
  int c;
  while (scanf("%d",&m) != EOF){
	 memset(visited,false,sizeof(bool)*m);
	 memset(pred,-1,sizeof(int)*m);
	 scanf("%d",&n);
	 for (int i=0; i < 10; ++i) digit[i] = false;
	 for (int i=0; i < n; ++i){
		scanf("%d",&c);
		digit[c] = true;
	 }
	 if (m == 0){ puts("0"); continue; }
	 bfs();
	 if ( !visited[0] ) puts("0");
	 else {
		  print_path( 0 );
		  putchar('\n');
	 }
  }
  return 0;
}