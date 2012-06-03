#include<cstdio>
#include<climits>
const int MAX = 100000;
int main(){
  int n,m;
  int d;
  while (scanf("%d %d",&n,&m) && (n && m)){
		int a = MAX;
		for (int i=0; i < n; ++i){
		  scanf("%d",&d);
		  if (d < a) a = d;
		}
		int b = MAX;
		int c = MAX;
		for (int i=0; i < m; ++i){
		  scanf("%d",&d);
		  if (d <= b){ c = b; b = d; }
		  else if (d < c) c = d;
		}
		if (a < c) puts("Y");
		else puts("N");
  }
  return 0;
}