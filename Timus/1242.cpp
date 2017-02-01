#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
vector<int> D[1005];
vector<int> U[1005];
char s[100];

int main(){
  int n;
  int u,v;
  scanf("%d",&n);
  while (1){
	 scanf("%s",s);
	 if ( strcmp(s,"BLOOD") == 0 ) break;
	 sscanf(s,"%d",&v); 
	 scanf("%d",&u);
	 u--,v--;
	 D[u].push_back(v); U[v].push_back(u);
  }
  vector<int> vis1(n,false);
  vector<int> vis2(n,false);
  queue<int> q1,q2;
  while ( scanf("%d",&u) != EOF ){
	 u--;
	 vis1[u] = true;
	 vis2[u] = true;
	 q1.push( u );
	 q2.push( u );
  }
  while ( !q1.empty() ){
	 u = q1.front();
	 q1.pop();
	 for ( int i=0; i < D[u].size(); ++i ){
		v = D[u][i];
		if ( !vis1[v] ){
		  vis1[v] = true;
		  q1.push(v);
		}
	 }
  }
  while ( !q2.empty() ){
	 u = q2.front();
	 q2.pop();
	 for ( int i=0; i < U[u].size(); ++i ){
		v = U[u][i];
		if ( !vis2[v] ){
		  vis2[v] = true;
		  q2.push(v);
		}
	 }
  }
  bool first = true;
  for ( int i=0; i<n; ++i ){
	 if ( !vis1[i] && !vis2[i] ){
		if ( first ) first = false;
		else printf(" ");
		printf("%d",i+1);
	 }
  }
  if ( !first ) printf("\n");
  else printf("0\n");
  return 0;
}