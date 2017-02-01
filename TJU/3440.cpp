#include<cstdio>
const int MOD = 1000000007;
long long seg_tree[ 25 * 50000 ];
int a[ 50002 ];

void build_tree(int n,int l,int r){
  if (l==r){
	 seg_tree[n] = a[l] % MOD;
	 return;
  }
  int m = (l + r) >> 1;
  build_tree(2*n,l,m);
  build_tree(2*n + 1,m+1,r);
  seg_tree[n] = (seg_tree[2*n] * seg_tree[2*n + 1]) % MOD;
}

void update(int n,int l,int r,int p,int v){
  if ( l==r ){
	 a[l] = v;
	 seg_tree[n] = a[l] % MOD;
	 return;
  }
  int m = (l + r) >> 1;
  if ( p <= m ) update(2*n,l,m,p,v);
  else update(2*n+1,m+1,r,p,v);
  seg_tree[n] = (seg_tree[2*n] * seg_tree[2*n + 1]) % MOD;
}

long long query(int n,int L,int R,int l,int r){
  if (L==l && R==r) return seg_tree[n];
  int m = (L + R) >> 1;
  if ( r <= m ) return query(2*n,L,m,l,r);
  if ( l > m  ) return query(2*n+1,m+1,R,l,r);
  return ( query(2*n,L,m,l,m) * query(2*n+1,m+1,R,m+1,r) ) % MOD;
}

int main(){
  int runs;
  int n;
  int q;
  int t,l,r;
  scanf("%d",&runs);
  while (runs--){
		scanf("%d",&n);
		for(int i=1; i <= n; ++i){
		  scanf("%d",a+i);
		}
		build_tree(1,1,n);
		scanf("%d",&q);
		while (q--){
			 scanf("%d %d %d",&t,&l,&r);
			 if (t)
				update(1,1,n,l,r);
			 else
				printf("%lld\n",query(1,1,n,l,r));
		}
  }
  return 0;
}