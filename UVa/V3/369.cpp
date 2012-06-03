#include<cstdio>
#include<algorithm>
using namespace std;

int a[105];

int comb( int n , int k ){
  if ( k == 0 ) return 1;
  if ( k == 1 ) return n;
  int m = 0;
  int g,t;
  for ( int i=(n-k)+1; i <= n; ++i ){
	 a[m++] = i;
  }
  for ( int i=2; i <= k; ++i ){
	 t = i;
	 for ( int j=0; j < m && t > 1 ; ++j ){
		if ( a[j] > 1 ){
		  g = __gcd(t,a[j]);
		  t /= g; a[j]/=g;
		}
	 }
  }
  int res = 1;
  for ( int i=0; i < m; ++i ) res*=a[i];
  return res;
}

int main(){
  int n,k;
  int res;
  while ( scanf("%d %d",&n,&k) && ( n || k ) ){
	 if ( k <= (n-k) ) res = comb(n,k);
	 else res = comb(n,n-k);
	 printf("%d things taken %d at a time is %d exactly.\n",n,k,res);
  }
  return 0;
}