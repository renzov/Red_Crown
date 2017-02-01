#include<cstdio>
int main(){
  int n,sum;
  puts("PERFECTION OUTPUT");
  while (scanf("%d",&n) && n){
		sum = 0;
		for (int i=1; i <= n/2; ++i){
			 if (n%i == 0)
				sum += i;
		}
		printf("%5d  ",n);
		if (sum == n) puts("PERFECT");
		else if (sum < n) puts("DEFICIENT");
		else puts("ABUNDANT");
  } 
  puts("END OF OUTPUT");
  return 0;
}