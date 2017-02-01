#include<cstdio>
#include<algorithm>
using namespace std;
int a[250001];
int main(){
  int n,i;
  scanf("%d",&n);
  for (i=0; i < n; ++i) scanf("%d",a+i);
  sort(a,a+n);
  if (n&1) printf("%d.0\n",a[n>>1]);
  else {
	 long long sum = (long long)a[n>>1] + a[(n>>1) - 1];
	 printf("%lld",sum>>1);
	 if (sum&1) printf(".5\n");
	 else printf(".0");
  }
  return 0;
}