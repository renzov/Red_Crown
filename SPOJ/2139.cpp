#include<cstdio>
#include<map>
#include<cstring>
#include<string>
#include<bitset>
using namespace std;

bitset<2101> G[2101];

int main(){
  int n,m;
  char cad[105];
  int u,v;

  scanf("%d %d",&n,&m);
  while (n){
	 map<string,int> hash;
	 for (int i=0; i < n; ++i){
		G[i].set(i);
		scanf("%s",cad);
		hash[ string(cad) ] = i;
	 }
	 for (int i=0; i < m; ++i){
		scanf("%s",cad);
		u = hash[ string(cad) ];
		scanf("%s",cad);
		v = hash[ string(cad) ];
		G[u] |= G[v];
		G[v] = G[u];
	 }
	 bool ok = true;
	 for (int i=0; i < n && ok; ++i){
		  if (G[i].count() < n) ok = false;
	 }
	 if (ok) printf("YES\n");
	 else printf("NO\n");
	 scanf("%d %d",&n,&m);
	 if (n){
		 for (int i=0; i < n; ++i)
			 G[i].reset();
	 }
  }
  return 0;
}