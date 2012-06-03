#include<cstdio>
#include<map>
#include<string>
using namespace std;
int n,m,q;
int G[35][35];

void floyd_warshall(){
  for (int k=0; k < n; ++k)
	 for (int i=0; i < n; ++i)
		for (int j=0; j < n; ++j)
			 if (i!=j && G[i][k] && G[k][j])
				if (!G[i][j] || G[i][j] > G[i][k] + G[k][j] )
				  G[i][j] = G[i][k] + G[k][j];
}

int main(){

  int runs;
  int cases = 0;
  char name[100];
  
  scanf("%d",&runs);
  
  puts("SHIPPING ROUTES OUTPUT");
  putchar('\n');

  while (runs--){
		scanf("%d %d %d",&n,&m,&q);
		cases++;

		printf("DATA SET  %d\n\n",cases);

		for (int i=0; i < n; ++i)
		  for (int j=0; j < n; ++j)
				G[i][j] = 0;

		map<string,int> hash;

		for (int i=0; i < n; ++i){
			 scanf("%s",name);
			 hash[string(name)] = i;
		}

		int u,v,w;

		for (int i=0; i < m; ++i){
		  	 scanf("%s",name);
			 u = hash[string(name)];
		    scanf("%s",name);
			 v = hash[string(name)];
			 G[u][v] = G[v][u] = 1;
		}

		floyd_warshall();

		for (int i=0; i < q; ++i){
			scanf("%d",&w);
			scanf("%s",name);
			 u = hash[string(name)];
		    scanf("%s",name);
			 v = hash[string(name)];
			 if (G[u][v] || u == v){
				  printf("$%d\n",w*100*G[u][v]);
			 }
			 else {
				  puts("NO SHIPMENT POSSIBLE");
			 }
		}
		putchar('\n');
  }

  puts("END OF OUTPUT");

  return 0;
}