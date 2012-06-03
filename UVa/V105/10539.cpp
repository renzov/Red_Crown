#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
bool nsp[ 1000002 ] = {0};
long long v[ 100000 ];
int n;

long long up = 1000000000000LL;
void sieve(){
  int i,j;
  long long num;
  n = 0;
  for ( i=4;  i < 1000000  ; i+=2 ) nsp[ i ] = true;
  num = 4;
  while ( num < up ){ v[n++] = num; num*=2LL; }
  for ( i = 3; i < 1000000 ; i+=2 ){
	 if ( !nsp[ i ] ){
		for ( j = 2*i; j < 1000000 ; j += i ) nsp[j] = true;
		num = ((long long)i)*i;
		while ( num < up ){ v[n++] = num; num*=i; }
	 }
  }
  sort( v , v + n );
}

int main(){
  sieve();
  long long low,high;
  int runs,a,b;
  scanf("%d",&runs);
  while ( runs-- ){
	 scanf("%lld %lld",&low,&high);
	 a = lower_bound(v,v+n,low) - v;
	 b = lower_bound(v,v+n,high) - v;
	 if ( high < v[0] ) printf("0\n");
	 else if ( a == n ) printf("0\n");
	 else if ( v[a] > high ) printf("0\n");
	 else {
		if ( b==n ) b--;
		if ( v[b] > high ) b--;
		printf("%d\n",b - a + 1);
	 }
  }
  return 0;
}