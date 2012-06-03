#include<cstdio>
const int MAX = 100005;
const int INF = -1000100;

int frec[MAX];
int a[MAX];
int seg_tree[MAX * 4];

inline int max(int x,int y){ return x>=y? x:y; }
void build_tree(int n,int l,int r){
  if (l==r){ seg_tree[n] = frec[l]; return; }
  int m = (l+r) >> 1;
  build_tree(n<<1,l,m);
  build_tree((n<<1)+1,m+1,r);
  seg_tree[n] = max( seg_tree[n<<1] , seg_tree[ (n<<1) + 1 ] );
}

int query(int n,int L,int R,int l,int r){
  if (l > r) return 0;
  if (l==L && r==R){ return seg_tree[n]; }
  int M = (L + R ) >> 1;
  if ( r <= M ) return query( n << 1 , L , M, l, r);
  if ( l > M ) return query( (n<<1) + 1, M+1, R, l, r);
  return max( query( n << 1 , L , M, l, M) , query( (n<<1) + 1, M+1, R, M+1, r) );
}

int main(){
  int n,q;
  int l,r;
  int last; 
  while (scanf("%d",&n) && n){
	 scanf("%d",&q);
	 a[0] = -1000000000;
	 for (int i=1; i <= n; ++i){ 
		scanf("%d",a+i);
		if ( a[i-1] == a[i] ) frec[i] = frec[i-1] + 1;
		else frec[i] = 1;
	 }
	 build_tree(1,1,n);
	 for (int i=0; i < q; ++i){
		scanf("%d %d",&l,&r);
		for (last=l; last <= r; last++) if (frec[last] == 1) break;
		int res = last - l;
		printf("%d\n",max(res,query(1,1,n,last,r)));
	 }
  }
  return 0;
}