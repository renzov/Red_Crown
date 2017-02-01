#include<cstdio>
#include<algorithm>
using namespace std;

long long a[5005];
long long c[5005];
long long b[5005];

int main(){
  int n,m;
  long long last;
  int idx;
  long long res;

  while ( scanf("%d",&n) != EOF ){
	 for ( int i=0; i < n; ++i ) scanf("%lld",a+i);
	 sort( a , a + n );
	 last = -1;
	 m = -1;
	 for (int i=0; i < n; i++){
		if ( last != a[i] ){ m++; last = a[i]; b[m] = last; c[m] = 1;  }
		else c[m]++;
	 }
	 m++;
	 res = 0LL;
	 for ( int i=0; i < m-1; ++i ){
		for ( int j=i+1; j < m-1; ++j ){
		  idx = lower_bound( b , b + m , b[i] + b[j] ) - b;
		  if ( idx < m && b[idx] == ( b[i] + b[j] ) ){
			 res += c[i]*c[j]*c[idx];
		  }
		}
		idx = lower_bound( b , b + m , b[i] << 1 ) - b;
		if ( idx < m && b[idx] == ( b[i] << 1 ) ){
		  res += ((c[i]*(c[i]-1))>>1)*c[idx];
		}
	 }
	 printf("%lld\n",res);
  }
  return 0;
}