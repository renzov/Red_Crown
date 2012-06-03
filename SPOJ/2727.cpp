#include<cstdio>
int main(){
  int n,m;
  int bestMG,bestG;
  int a;
  int runs;
  scanf("%d",&runs);
  while (runs--){
		scanf("%d %d",&n,&m);
		bestG = bestMG = -1;
		for (int i=0; i < n; ++i){ 
		  scanf("%d",&a); 
		  if (a > bestG) bestG = a;
		}
		for (int i=0; i < m; ++i){ 
		  scanf("%d",&a);
		  if (a > bestMG) bestMG = a;
		}
		if (bestG >= bestMG) puts("Godzilla");
		else puts("MechaGodzilla");
  }
  return 0;
}