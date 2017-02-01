#include<cstdio>
#include<algorithm>
using namespace std;
const int MAX = 10000;
const int MOD = 5000000;
int a[ MAX + 2 ];
int p[ MAX + 2 ];
int ord[ MAX  + 2];
int dp[ MAX + 2 ][ 52 ] = {0};
int seg_tree[ 52 ][ 4*MAX ] = {0};

void update(int N,int t,int pos,int v){
  int m;
  int n = 1;
  int l = 1;
  int r = N;
  while (l!=r){
	 seg_tree[ t ][ n ] = (seg_tree[t][n] + v) % MOD;
	 m = (l+r)>>1;
	 n<<=1;
	 if (pos <= m){ r = m; }
	 else { l = m+1; n++; }
  }
  seg_tree[ t ][ n ] = (seg_tree[t][n] + v) % MOD;
}

int query(int t, int n , int L , int R , int l , int r){
  if (l>r) return 0;
  if (r==R && L==l) return seg_tree[t][n];
  int M = (L+R) >> 1;
  if ( r <= M ) return query( t , n<<1 , L , M , l , r );
  if ( l > M ) return query( t , (n<<1) + 1, M + 1 , R , l , r );
  return ( query(  t , n<<1 , L , M , l , M ) + query( t , (n<<1) + 1, M + 1 , R , M + 1 , r ) )%MOD;
}

int main(){
  int n,k;
  scanf("%d %d",&n,&k);
  for (int i=0; i < n; ++i){ scanf("%d",a+i); ord[i] = a[i]; }
  sort(ord,ord+n);
  for (int i=0; i < n; ++i) p[i] = (lower_bound(ord,ord+n,a[i]) - ord) + 1;
  for (int i=0; i < n; ++i) dp[i][1] = 1;
  for (int j=2; j <= k; ++j){
	 for (int i=n-2; i >= 0; --i){
		update(n,j,p[i+1],dp[i+1][j-1]);
		dp[i][j] = (dp[i][j] + query( j ,  1 , 1 , n , p[i] + 1 , n )) % MOD;
	 }
  }
  int res = 0;
  for (int i=0; i < n; ++i)
	 res = ( res + dp[i][k] ) % MOD;
  printf("%d\n",res);
  return 0;
}