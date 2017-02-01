#include<cstdio>
#include<algorithm>
using namespace std;

int main(){
  int x[1005];
  int y[1005];
  int runs;
  int n;
  int dot;
  scanf("%d",&runs);
  while (runs--){
		scanf("%d",&n);
		dot = 0;
		for (int i=0; i < n; ++i) scanf("%d",x+i);
		for (int i=0; i < n; ++i) scanf("%d",y+i);
		sort(x,x+n);
		sort(y,y+n);
		for (int i=0; i < n; ++i) dot += x[i]*y[i];
		printf("%d\n",dot);
  }
  return 0;
}