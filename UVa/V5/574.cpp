#include<cstdio>
#include<algorithm>
using namespace std;

int a[ 14 ];
int sol[ 14 ];
int sum[14] = {0};
int n,t;
int cnt;

void backtrack( int total, int idx , int pos ){
  if ( total < 0 || (idx < 0 && total) ) return;
  int i;
  if ( total == 0 ){
	 cnt++;
	 for ( i = 0; i < pos; ++i ){
		if ( i ) putchar('+');
		printf("%d",sol[i]);
	 }
	 putchar('\n');
	 return;
  }
  int last = -1;
  for ( i=idx; i >= 0 && sum[i] >= total; --i ){
	 if ( a[i] <= total ){
		if ( last != a[i] ){
		  sol[ pos ] = a[i];
		  backtrack( total - a[i] , i - 1 , pos + 1 );
		  last = a[i];
		}
	 }
  }
}

int main(){
  int i;
  int j,k;
  while (scanf("%d %d",&t,&n) && n){
	 for ( i=0; i < n; ++i ){ scanf("%d",a+i); sum[i] = ( (i? sum[i-1]:0) + a[i] ); }
	 cnt = 0;
	 printf("Sums of %d:\n",t);
	 sort( a , a + n  );
	 backtrack( t , n - 1 , 0 );
	 if ( !cnt ) puts("NONE");
  }

  return 0;
}