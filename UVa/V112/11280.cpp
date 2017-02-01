#include<cstdio>
#include<string>
#include<map>
#include<algorithm>
using namespace std;
const int INF = 999999999;
struct edge{
  int u,v,w;
};

edge E[1005];
int d[105];
int dp[105][105];
int n;
int m;
int q;

int main(){
  
  int runs;
  char name[50];
  int t;
  int u,v,w;
  int idx;

  scanf("%d",&runs);
  for (int k=1; k <= runs; ++k){
	 scanf("%d",&n);
	 map<string,int> hash;
	 for (int i=0; i < n; ++i){
		scanf("%s",name);
		hash[ string(name) ] = i;
	 }
	 scanf("%d",&t);
	 pair<int,int> tmp;
	 map< pair<int,int> , int > medge;
	 m = 0;
	 for (int i=0; i < t; ++i){
		scanf("%s",name);
		u = hash[ string(name) ]; 
		scanf("%s",name);
		v = hash[ string(name) ];
		scanf("%d",&w);
		tmp.first = u;
		tmp.second = v;
		if ( medge.find(tmp) == medge.end() ){
			 E[m].u = u;
			 E[m].v = v;
			 E[m].w = w;
			 medge[ tmp ] = m;
			 m++;
 		}
		else {
			 idx = medge[tmp];
			 if (E[idx].w > w) E[idx].w = w;
		}
	 }
	 
	 d[0] = 0;
	 dp[0][0] = 0;
	 for (int i=1; i < n; ++i){ 
		d[i] = INF;
		dp[i][0] = INF;
	 }
	 /* Bellman Ford */
	 for (int i=1; i <= n-1; ++i){
		  for (int j=0; j < m; ++j){
				u = E[j].u;
				v = E[j].v;
				w = E[j].w;
				if (d[u] < INF){
					 if (d[u] + w < d[v]){
						d[v] = d[u] + w;
					 }
				}
		  }
		  printf("iteracion %d\n",i);
		  for (int j=0; j < n; ++j){
			 dp[j][i] = d[j];
			 printf(" %d",dp[j][i]);
		  }
		  putchar('\n');
	 }
	 
	 if (k > 1) putchar('\n');

	 printf("Scenario #%d\n",k);
	 scanf("%d",&q);
	 for (int i=0; i < q; ++i){
		  scanf("%d",&w);
		  w = min(w+1,n-1);
		  printf("W = %d\n",w);
		  if (dp[n-1][w] < INF) printf("Total cost of flight(s) is $%d\n",dp[n-1][w]);
		  else printf("No satisfactory flights\n");
	 }
	 
  }

  return 0;
}
