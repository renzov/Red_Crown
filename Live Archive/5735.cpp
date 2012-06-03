#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;

pair<int,int> a[ 1000005 ];

int main(){
  int cases = 0;
  int n,k1,k2,v;
  int b[105];
  while ( scanf("%d %d %d",&n,&k1,&k2) && n ){
	 cases++;
	 for (int i=0; i < n; ++i){
		scanf("%d",&v);
		a[i].first = v;
		a[i].second = i+1;
	 }
	 sort(a,a+n);
	 printf("Case %d\n",cases);
	 for (int i=0; i < k1; ++i){
		b[i] = a[i].second;
	 }
	 sort( b , b + k1 );
	 for (int i=0; i < k1; ++i){
		if (i>0) putchar(' ');
		printf("%d",b[i]);
	 }
	 putchar('\n');
	 for(int i=0,j=n-1; i < k2; ++i,--j){
		b[i] = a[j].second;
	 }
	 sort( b , b + k2 );
	 for (int i=k2-1; i >= 0; --i){
		printf("%d",b[i]);
		if ( i > 0 ) putchar(' ');
	 }
	 putchar('\n');
  }
  return 0;
}