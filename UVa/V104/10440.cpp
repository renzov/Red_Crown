#include<cstdio>

int main(){

  int n,t,m;
  int runs;
  int a[1444];
  int nt;
  int left;
  
  scanf("%d",&runs);
  while (runs--){
		scanf("%d %d %d",&n,&t,&m);
		t<<=1;
		nt = (m + n - 1)/n;
		left = m - (nt-1)*n;
		for (int i=0; i < left; ++i) scanf("%d",a);
		for (int i=1; i < nt; ++i){
			 for (int j=0; j < n; ++j)
				  scanf("%d",a+i);
		}
		for (int i=0; i < (nt-1); ++i){
			 if (a[i]+t > a[i+1]) a[i+1] = a[i] + t;
		}
		printf("%d %d\n",a[nt-1] + t/2,nt);
  }
  return 0;
}