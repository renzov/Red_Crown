#include<cstdio>
#include<climits>

int d[205] = {0};
int a[105];
int b[105];
int best;
int n;

void dfs(int p){
	if ( p + d[a[p]] >= best) return;
	if (a[p] == n){
		best = p;
		for (int i=0; i <= p; ++i) b[i] = a[i];
		return;
	}
	for(int i=p; i >= 0; --i)
	  for (int j=p; j >= i; --j)
		  if ( (a[i]+a[j] > a[p]) && (a[i] + a[j] <= n) ){
			 a[p+1] = a[i] + a[j];
			 dfs( p+1 );
		  }
}

void pre_calc(){
 for (int i=n+n; i >= n; i--) d[i] = 0;
 for (int i=n-1; i >= 1; --i) d[i] = 1 + d[i<<1];
 a[0] = 1;
 best = INT_MAX;
 dfs(0);
 for (int i=0;i < best; ++i)
	 printf("%d ",b[i]);
 printf("%d\n",b[best]);
}

int main(){
  while (scanf("%d",&n) && n){
	 pre_calc();
  }
  return 0;
}