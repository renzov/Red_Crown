#include<cstdio>
#include<algorithm>
using namespace std;
const int MAX = 20010;
struct poster{
  int l,r;
};
struct point{
  int x;
  int p;
  bool operator<(const point &that) const {
	 return x < that.x;
  }
};

point lst[ 30010 ];
poster a[ 20010 ];
bool found[ 20010 ];
int seg_tree[ 4 * MAX];
int res = 0;

void build_tree(int n,int l,int r){
  seg_tree[n] = 0;
  if (l==r) return;
  int m=(l+r)>>1;
  build_tree(n<<1,l,m); build_tree((n<<1)+1,m+1,r);
}

void countColor(int n){
  if ( seg_tree[n] > 0 ){
	 if ( !found[ seg_tree[n] ] ){
		  found[ seg_tree[n] ] = true;
		  res++;
	 }
	 return;
  }
  countColor(n<<1);
  countColor((n<<1) + 1);
}

void update( int n , int L , int R , int l ,int r , int c ){
  if (R == r && l == L){ seg_tree[n] = c; return; }
  if (seg_tree[n] > 0 && seg_tree[n] != c){
	 seg_tree[n<<1] = seg_tree[(n<<1) + 1] = seg_tree[n];
	 seg_tree[n] = 0;
  }
  int M = (L+R) >> 1;
  if (r <= M) update(n<<1,L,M,l,r,c);
  else if (l > M) update((n<<1) + 1,M+1,R,l,r,c);
  else {
	 update(n<<1,L,M,l,M,c);
	 update((n<<1) + 1,M+1,R,M+1,r,c);
  }
}

int main(){
  int runs;
  int m,n;
  int last;
  int l,r;
  scanf("%d",&runs);
  while (runs--){
	 scanf("%d",&m);
	 for (int i=0;i<m; ++i){
		  scanf("%d %d",&l,&r);
		  lst[ i << 1 ].x = l; 
		  lst[ i << 1 ].p = -(i+1);
		  lst[ (i << 1) + 1 ].x = r; 
		  lst[ (i << 1) + 1].p = (i+1);
	 }
	 sort( lst , lst + (m<<1) );
	 last = lst[0].x;
	 n = 1;
	 for (int i=0; i < (m<<1); ++i){
		if ( last != lst[i].x ){ n++; last = lst[i].x; }
		if ( lst[i].p < 0 ) a[ -lst[i].p - 1 ].l = n;
		else a[ lst[i].p - 1 ].r = n;
	 }
	 build_tree(1,1,n);
	 for (int i=0; i < m; ++i){
		found[i+1] = false;
		update( 1 , 1 , n , a[i].l , a[i].r , i+1 );
	 }
	 res = 0;
	 countColor(1);
	 printf("%d\n",res);
  }
  return 0;
}