#include<cstdio>
#include<algorithm>
using namespace std;
const int MAX = 200005 * 4; 
int seg_tree[ MAX ];
int a[200005];
int ord[200005];

void build_tree(int n,int l,int r){
	 seg_tree[n] = 0;
	 if (l==r) return;
	 int m = (l+r) >> 1;
	 build_tree(2*n,l,m); build_tree(2*n+1,m+1,r);
}

int query(int n,int L,int R,int l,int r){
	 if (L==l && r==R) return seg_tree[n];
	 int M = (L+R)>>1;
	 if (r <= M) return query(2*n,L,M,l,r);
	 if (l > M) return query(2*n+1,M+1,R,l,r);
	 return query(2*n,L,M,l,M) + query(2*n+1,M+1,R,M+1,r);
}

void update(int N,int p){
  int l = 1;
  int r = N;
  int m;
  int n = 1;
  while (l!=r){
	 seg_tree[n]++;
	 m = (l+r) >> 1;
	 if (p <= m){ n*=2; r = m; }
	 else { n*=2; n++; l = m+1; }
  }
  /* l == r -> llegamos a la hoja */
  seg_tree[n]++;
}

int main(){
  int n;
  int runs;
  long long res;
  int idx;
  scanf("%d",&runs);
  while (runs--){
	 scanf("%d",&n);
	 build_tree(1,1,n);
	 for (int i=0; i< n ; ++i){
		scanf("%d",a+i);
		ord[i] = a[i];
	 }
	 sort(ord,ord+n);
	 res = 0;
	 for (int i=0; i < n; ++i){
		idx = lower_bound( ord, ord + n, a[i] ) - ord;
		res += query( 1 , 1 , n, idx + 1 , n );
		update(n,idx+1);
	 }
	 printf("%lld\n",res);
  }
  return 0;
}