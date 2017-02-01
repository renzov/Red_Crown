#include<cstdio>
#include<algorithm>
using namespace std;
int a[1005];
int main(){
  int n;
  int s;
  int runs;
  int sum;
  int res;
  scanf("%d",&runs);
  for (int k=1; k <= runs; ++k){
	 scanf("%d %d",&s,&n);
	 sum = 0;
	 for (int i=0; i<n; ++i) scanf("%d",a+i),sum += a[i];
	 printf("Scenario #%d:\n",k);
	 if (sum < s) puts("impossible");
	 else {
		 sort(a,a+n);
		 sum = 0;
		 res = 0; 
		 for (int i=n-1; i >= 0 && sum < s; --i){
			 res++;
			 sum += a[i];
		 }
		 printf("%d\n",res);
	 }
	 putchar('\n');
  }
  return 0;
}