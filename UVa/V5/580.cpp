#include<cstdio>
int main(){

  int v[31];
  int n;
  v[1] = 2;
  v[2] = 4;
  v[3] = 7;
  for ( int i=4; i <= 30; ++i ){
	 v[i] = v[i-1] + v[i-2] + v[i-3];
  }
  while ( scanf("%d",&n) &&  n ){
	 printf("%d\n",(1<<n) - v[n]);
  }
  return 0;
}