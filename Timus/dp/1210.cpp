#include<cstdio>
#include<climits>

int main(){
  
  int n;
  int m;
  int v,w;
  int best;
  char ex[6];
  int prev[ 35 ];
  int next[ 35 ];
  prev[ 1 ] = 0;
  
  scanf("%d",&n);
  for (int i=1; i <= n; ++i){
	 scanf("%d",&m);
	 best = INT_MAX;
	 for (int j=1; j <= m; ++j){
		next[j] = INT_MAX;
		while (scanf("%d",&v) && v){
		  scanf("%d",&w);
		  if (prev[v] + w < next[j])
			 next[j] = prev[v] + w;
		}
		if (best > next[j]) best = next[j]; 
	 }
	 for (int j=1; j <= m; ++j)
		  prev[j] = next[j];
	 scanf("%s",ex);
  }
  printf("%d\n",best);
  return 0;
}