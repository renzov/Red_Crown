#include<cstdio>
#include<algorithm>
using namespace std;
int main(){
  int n,k,s;
  int a[1005];

  scanf("%d %d %d",&n,&k,&s);
  for (int i=0; i < n; ++i) scanf("%d",a+i);
  sort(a,a+n);
  int res = 0;
  int sum = 0;
  for (int i=n-1; i >= 0 && sum < (k*s); --i) sum += a[i],res++;
  printf("%d\n",res);
  return 0;
}