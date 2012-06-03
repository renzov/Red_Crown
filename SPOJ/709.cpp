#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;
int seg_tree[ 100 * 100002 ];
pair< int , pair<int,int> > a[100002];

inline int Min(int x , int y){
  return (x < y)? x:y;
}

void build_tree(int n,int l,int r){
  seg_tree[n] = INT_MAX;
  if (l==r) return;
  int m = (l + r) >> 1;
  build_tree(2*n,l,m);
  build_tree(2*n+1,m+1,r);
}

void update(int n,int l,int r,int p,int v){
  if (l==r){ seg_tree[ n ] = v; return; }
  int m = (l  + r ) >> 1;
  if (p <= m) update(2*n,l,m,p,v);
  else update(2*n+1,m+1,r,p,v);
  seg_tree[n] = Min(seg_tree[2*n],seg_tree[2*n+1]);
}

int query( int n , int L , int R,int l, int r){
  if (l==L && r==R) return seg_tree[n];
  int m = (L  + R) >> 1;
  if (r <= m) return query(2*n,L,m,l,r);
  if (l > m) return query(2*n+1,m+1,R,l,r);
  return Min( query(2*n, L, m , l,m) , query( 2*n+1 , m+1,R, m+1,r ) );
}

int main(){
  int runs;
  int n;
  scanf("%d",&runs);
  int res = 0;
  while (runs--){
		scanf("%d",&n);
		build_tree(1,1,n);
		for (int i=0;  i < n; ++i){
			 scanf("%d %d %d",&a[i].first,&a[i].second.first,&a[i].second.second);
		}
		sort(a, a + n);
		for (int i=0; i < n; ++i){
		  if ( query( 1 , 1 , n , 1 , a[i].second.first ) > a[i].second.second ) res++;
		  update(1,1,n,a[i].second.first,a[i].second.second);
		}
		printf("%d\n",res);
  }
  return 0;
}