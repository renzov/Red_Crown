#include<cstdio>
#include<map>
#include<string>
using namespace std;

double G[35][35];

int main(){
  char name[100];
  char to[100];
  int m;
  int n;
  double f;
  int u,v;
  int cases = 0;
  while ( scanf("%d",&n) && n){
	 cases++;
	 map<string,int> hash;
	 for (int i=0;  i<n; ++i){
		scanf("%s",name);
		hash[ string(name) ] = i;
	 }
	 for (int i=0; i < n; ++i){
		G[i][i] = 0.0;
		for (int j=i+1; j < n; ++j){
		  G[j][i] = G[i][j] = 0.0;
		}
	 }
	 scanf("%d",&m);
	 while ( m-- ){
		scanf("%s %lf %s",name,&f,to);
		u = hash[string(name)];
		v = hash[string(to)];
		G[u][v] = f;
	 }

	 for (int i=0; i<n; ++i) 
		G[i][i] = max(G[i][i],1.0);

	 for (int k=0; k < n; ++k)
		for (int i=0; i < n; ++i)
		  for (int j=0; j < n; ++j)
			 G[i][j] = max( G[i][j] , G[i][k] * G[k][j]);

	 bool found = false;
	 for (int i=0; i < n && !found; ++i) if (G[i][i] > 1.0) found = true;
	 if (found) printf("Case %d: Yes\n",cases);
	 else printf("Case %d: No\n",cases);
  }
  
  return 0;
}