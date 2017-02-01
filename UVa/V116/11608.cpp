#include<cstdio>
int main(){
  int sum[15];
  int runs = 0;
  int d;
  while (scanf("%d",sum) && sum[0] >= 0){
		runs++;
		for (int i=0; i < 12; ++i){ scanf("%d",sum+i+1); sum[i+1] += sum[i]; }
		printf("Case %d:\n",runs);
		for (int i=0; i < 12; ++i){
			scanf("%d",&d);
			if (sum[i] >= d) { 
			    puts("No problem! :D"); 
				 for (int j=i+1; j < 12; ++j)
					 sum[j]-=d;
		   } 
		   else puts("No problem. :(");
		}
  }
  return 0;
}