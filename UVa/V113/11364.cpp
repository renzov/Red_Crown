#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;
inline int abs(int x){
  return x < 0 ? -x:x;
}

int a[25];

int main(){

  int n;
  int runs;
  int res;
  scanf("%d",&runs);
  
  while (runs--){
	 scanf("%d",&n);
	 res = 0;
	 for (int i=0; i < n; ++i){
		scanf("%d",a+i);
		//if (i > 0) res+=abs(a[i]-a[i-1]);
	 }
	 sort(a,a+n);
	 for (int i=0; i < n; ++i){
		//scanf("%d",a+i);
		if (i > 0) res+=abs(a[i]-a[i-1]);
	 }
	 int mini = INT_MAX;
	 int tmp;
	 for (int i=0; i < 100; ++i){
		 tmp = res + abs(a[0] - i) + abs(a[n-1] - i);
		 if (tmp < mini) mini = tmp;
	 }
	 printf("%d\n",mini);
  }

  return 0;
}