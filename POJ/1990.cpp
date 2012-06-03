#include<cstdio>
#include<algorithm>
using namespace std;
const int MAX = 4 * 20000;
int seg_tree_cnt[ MAX ] = {0};
int seg_tree_sum[ MAX ] = {0};

pair<int,int> a[20003];
int ord[20003];

pair<int,int> query(int n,int L,int R,int l,int r){
  if (L==l && r==R) return make_pair( seg_tree_sum[n] , seg_tree_cnt[n] );
  int M = (L+R) >> 1;
  if (r <= M) return query( 2*n , L, M, l, r);
  if (l > M) return query( 2*n+1 , M + 1, R, l , r);
  pair<int,int> t1 = query( 2*n , L , M, l, M);
  pair<int,int> t2 = query( 2*n + 1, M + 1, R, M + 1, r);
  return make_pair( t1.first + t2.first , t1.second + t2.second );
}

void update(int N,int p,int v){
  int L = 1;
  int R = N;
  int M;
  int n = 1;
  while ( L != R ){
	 seg_tree_cnt[n]++;
	 seg_tree_sum[n] += v;
	 M = (L + R) >> 1;
	 if ( p <= M ){ n<<=1; R = M; }
	 else { n = 2*n + 1; L = M + 1; }
  }
  seg_tree_cnt[n]++;
  seg_tree_sum[n] += v;
}

int main(){
  int n;
  int idx;
  long long res = 0;
  pair<int,int> left;
  pair<int,int> right;
  scanf("%d",&n);
  for (int i=0; i < n; ++i){	scanf("%d %d",&a[i].first,&a[i].second); ord[i] = a[i].second; }
  sort(a,a+n);
  sort(ord,ord + n);
  for (int i=0; i < n; ++i){
	 idx = lower_bound( ord , ord + n, a[i].second) - ord;
	 idx++;
	 left = query(1,1,n,1,idx);
	 res += ( (long long)a[i].second*left.second - left.first ) * a[i].first;
	 right = query(1,1,n,idx,n);
	 res += ( right.first - (long long)a[i].second*right.second ) * a[i].first;
	 update(n,idx,a[i].second);
  }
  printf("%lld\n",res);
  return 0;
}