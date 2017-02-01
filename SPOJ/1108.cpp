#include<cstdio>
int seg_tree[4*20005];
void build_tree(int n,int l,int r){
  seg_tree[n] = r - l + 1;
  if (l!=r) {
		int m = (l + r) >> 1;
		build_tree(2*n,l,m);
		build_tree(2*n + 1,m+1,r);
  }
}

int get_index(int n,int l,int r,int sum){
	 if (l==r) return l;
	 int m = (l+r)>>1;
	 if (seg_tree[2*n] < sum){
		  return get_index(2*n+1,m+1,r,sum - seg_tree[2*n]);
	 }
	 else {
		  return get_index( 2*n , l , m, sum );
	 }
}

void update(int n,int l,int r,int x){
  if (l==r){ seg_tree[n] = 0; }
  else {
	 int m = (l + r) >> 1;
	 if (x <= m) update(2*n,l,m,x);
	 else update(2*n+1,m+1,r,x);
	 seg_tree[n] = seg_tree[2*n] + seg_tree[2*n + 1];
  }
}

int a[20005];

int main(){
  int runs;
  int p;
  int idx;
  int m;
  int sum;
  int n;
  scanf("%d",&runs);
  while (runs--){
		scanf("%d",&n);
		build_tree(1,1,n);
		p = 0; m = n;
		for (int i=1; i <= n; ++i,--m){
		  sum = (p + i + 1)%m;
		  if (!sum) sum = m;
		  idx = get_index(1,1,n,sum);
		  update(1,1,n,idx);
		  p = sum - 1;
		  a[idx] = i;
		}
		for (int i=1; i <= n; ++i){
			 if (i > 1) putchar(' ');
			 printf("%d",a[i]);
		}
		putchar('\n');
  }
  return 0;
}