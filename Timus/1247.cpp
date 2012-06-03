#include<cstdio>

int a[30005];

int main(){
  int n,s;
  scanf("%d %d",&n,&s);
  for (int i=1; i <= n; ++i){ scanf("%d",a+i); a[i]--; }
  int bi,bj;
  int j;
  int max = -1;
  int sum = 0;
  bi = bj = 0;
  j = 1;
  for ( int i=1; i <= n; ++i ){
	 sum += a[i];
	 if ( sum > max ){ bi = j; bj = i; max = sum; }
	 if ( sum < 0 ){ sum = 0; j = i+1; }
  }
  if ( max > s ) puts("NO");
  else puts("YES");
  return 0;
}