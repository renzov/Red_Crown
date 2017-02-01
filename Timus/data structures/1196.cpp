#include<cstdio>
#include<algorithm>
using namespace std;
int a[15005];
int main(){
  int n,m;
  int x,res=0;
  scanf("%d",&n);
  for (int i=0; i < n; ++i) scanf("%d",a+i);
  scanf("%d",&m);
  while (m--){
	 scanf("%d",&x);
	 if (binary_search(a,a+n,x)) res++;
  }
  printf("%d\n",res);
  return 0;
}