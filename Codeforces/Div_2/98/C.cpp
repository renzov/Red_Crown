#include<cstdio>
#include<algorithm>
#include<map>
#include<climits>
using namespace std;

int sum[ 4 * 200005 ] = {0};

void update( int node, int l, int r, int p,int val ){
  int m;
  while ( l != r ){
	 sum[node] += val;
	 m = ( l + r ) >> 1;
	 if ( p <= m ){
		node <<= 1; r = m;
	 }
	 else {
		node <<= 1; node++;
		l = m+1;
	 }
  }
  sum[node] += val;
}

int get_sum( int node, int l,int r,int p ){
  if ( r < p || l > p ) return 0;
  if ( l==r || p == r ) return sum[node];
  int m = ( l + r ) >> 1;
  if ( p <= m ) return get_sum(node<<1,l,m,p);
  return sum[node<<1] + get_sum( (node<<1) + 1, m + 1, r, p );
}

pair<int,int> a[ 200005 ];

int main(){
  int l,r;
  int n,m;
  int res = 0;
  int idx;
  map<int,int> H;
  map<int,int> B;
  
  scanf("%d",&n);
  for ( int i=0; i < n; ++i ){
		scanf("%d %d",&l,&r);
		H[r] = l;
		a[m].first = l; a[m].second = 0; m++;
		a[m].first = r; a[m].second = 1; m++;
  }
  sort( a , a + m );
  for ( int i=0; i < m; ++i ){
	 if ( a[i].second == 0 ){
		B[ a[i].first ] = i;
		update(1,1,m,i+1,1);
	 }
	 else {
		l = H[ a[i].first ];
		idx = B[ l ];
		if ( get_sum(1,1,m,idx) ){ res++; }
		update(1,1,m,idx+1,-1);
	 }
  }
  printf("%d\n",res);
  return 0;
}