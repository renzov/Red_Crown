#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
#define forn(i,n) for( int i=0; i < (int)(n); ++i )

long long mask[25];


int main(){
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  int n,m,k,v;
  scanf("%d %d",&n,&m);
  forn(i,n){
	 mask[i] = 0;
	 scanf("%d",&k);
	 forn(j,k){
		scanf("%d",&v); v--; mask[i] |= ( 1LL << v );
	 }
  }
  int best = 50;
  int bm;
  int bits;
  long long dest;
  long long total = (1LL<<m) - 1;
  for ( int i=1; i < (1<<n); ++i ){
	 bits = __builtin_popcount( i );
	 if ( best <= bits ) continue;
	 dest = 0;
	 forn(j,n){
		if ( (i >> j)&1 ){
		  dest |= mask[j];
		}
	 }
	 if ( dest == total ){
		best = bits; bm = i;
	 }
  }
  printf("%d\n",best);
  bool first = true;
  forn(i,n){
	 if ( (bm>>i) & 1 ){
		if ( !first ) printf(" ");
		else first = false;
		printf("%d",i+1);
	 }
  }
  printf("\n");
  return 0;
}