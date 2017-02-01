#include<cmath>
#include<cstdio>

int main(){
  int n,r,sum;
  int runs;
  scanf("%d",&runs);
  while (runs--){
		scanf("%d",&n);
		r = (int) sqrt(n);
		sum = 0;
		if (n==1) sum = 0;
		else sum = 1;
		if ((r+1)*(r+1) <= n) r++;
		for (int i=2; i <= r && i < n; ++i) 
		  if (n%i == 0){ 
			 sum += i;
			 if (n/i != i) sum += n/i;
		  }
		printf("%d\n",sum);
  }


  return 0;
}