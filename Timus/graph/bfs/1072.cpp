#include<cstdio>
#include<vector>
#include<queue>

using namespace std;

vector<int> G[ 100 ];
int n;
vector< int > t[ 100 ];
int pred[ 100 ];
int d[ 100 ];

void printSol(int u){
  if (pred[u] == -1){
	 printf("%d",u+1);
  }
  else {
	 printSol(pred[u]);
	 printf(" %d",u+1);
  }
  
}

int main(){
  
  int a1,a2,a3,a4;
  int m;
  int ip,network;
  
  scanf("%d",&n);
  
  for (int i=0; i < n; ++i){
	 pred[ i ] = d[ i ] = -1;
	 scanf("%d",&m);
	 t[i].resize( m );
	 for (int j=0; j < m; ++j){
		scanf("%d.%d.%d.%d",&a1,&a2,&a3,&a4);
		ip = ( a1 << 24 ) | ( a2 << 16 ) | ( a3 << 8 ) | a4;
		scanf("%d.%d.%d.%d",&a1,&a2,&a3,&a4);
		network = ( a1 << 24 ) | ( a2 << 16 ) | ( a3 << 8 ) | a4;
		t[i][j] = ip & network;
	 }
  }
  
  bool found;
  
  for (int x=0; x < n; ++x){
	 for (int y=x+1; y < n; ++y){
		found = false;
		for (int w=0; w < t[x].size() && !found; ++w){
			 for (int z=0; z < t[y].size() && !found; ++z){
				  if (t[x][w] == t[y][z]) found = true;
			 }
		}
		if (found){
		  G[x].push_back(y);
		  G[y].push_back(x);
		}
	 }
  }
  int u,v,e;
  scanf("%d %d",&u,&e);
  u--,e--;
  queue<int> q;
  d[u] = 0; 
  q.push(u);
  while (!q.empty()){
	 u = q.front();
	 q.pop();
	 if (u==e) break;
	 for (int i=0; i < G[u].size(); ++i){
		v = G[u][i];
		if (d[v]==-1){
		  pred[v] = u;
		  d[v] = d[u] + 1;
		  q.push(v);
		}
	 }
  }
  if (d[e] > -1){
	 printf("Yes\n");
	 printSol(e);
	 putchar('\n');
  }
  else {
	 printf("No\n");
  }
  return 0;
}