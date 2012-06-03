#include<cstdio>
#include<algorithm>
using namespace std;

const int MAX = 4 * 500000;
int a[ 500002 ];
int ord[ 500002 ];
int seg_tree[MAX];

int update(int N,int p){
  int l = 1;
  int r = N;
  int m;
  int n = 1;
  while (l!=r){
	 seg_tree[n]++;
	 m = (l + r) >> 1;
	 if (p<=m){ r = m; n <<= 1; }
	 else { l = m+1; n<<=1; n++; }
  }
  seg_tree[n]++;
}
void build_tree(int n,int l,int r){
  seg_tree[n] = 0;
  if (l==r) return;
  int m = (l+r) >> 1;
  build_tree(n<<1,l,m); build_tree( (n<<1) + 1, m+1, r);
}

long long query(int n,int L,int R,int l,int r){
  if (L==l && r == R) return seg_tree[n];
  int M = (L + R) >> 1;
  if (r <= M) return query( n << 1, L , M, l, r );
  if (M < l) return query((n<<1) + 1 , M + 1, R, l, r);
  return query( n << 1, L , M, l, M ) + query( (n<<1) + 1 , M + 1, R, M + 1, r );
}

int main(){
  int n;
  int idx;
  long long res;
  while (scanf("%d",&n) && n){
	 for (int i=0; i < n; ++i){ scanf("%d",a+i); ord[i]=a[i]; }
	 sort(ord,ord + n);
	 res = 0;
	 build_tree(1,1,n);
	 for (int i=0; i < n; ++i){
		idx = lower_bound(ord,ord + n,a[i]) - ord;
		idx++;
		res += query(1,1,n,idx,n);
		update(n,idx);
	 }
	 printf("%lld\n",res);
  }
  return 0;
}