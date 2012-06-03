#include<cstdio>
int p[100002];
bool elim[100001]= {0};
int edge[100001][2];
int Q[100001];
int res[100001];
int nset;

void make_set(int x){ p[x] = x; }
int find_set(int x){ return x!=p[x]? (p[x]=find_set(p[x])):x; }
void union_set(int x,int y){ if (x==y) return; nset--; p[y] = x; }

int main(){
  int i,q,n,m;
  scanf("%d %d",&n,&m);
  nset = n;
  for (i=1; i <= n; ++i) make_set( i );
  for (i=0; i < m; ++i) scanf("%d %d",&edge[i][0],&edge[i][1]);
  scanf("%d",&q);
  for (i=0; i < q; ++i){ scanf("%d",Q+i); Q[i]--; elim[ Q[i] ] = true; }
  for (i=0; i < m; ++i) if (!elim[i]) union_set( find_set( edge[i][0] ) , find_set( edge[i][1] ) );
  for (i=q-1; i>=0; --i){
	 res[i] = nset;
	 union_set( find_set( edge[ Q[i] ][0] ) , find_set( edge[ Q[i] ][1] ) ); 
  }
  printf("%d",res[0]);
  for (i=1; i < q; ++i) printf(" %d",res[i]);
  putchar('\n');
  return 0;
}