#include<cstdio>
long long X[200002];
long long Y[200002];

int main(){
  int n;
  scanf("%d",&n);
  for ( int i=0; i < n; ++i ){
	 scanf("%lld %lld",X+i,Y+i);
  }
  long long area = 0;
  X[n] = X[0];
  Y[n] = Y[0];
  for ( int i=0;i < n; ++i ){
	 area += (X[i]*Y[i+1] - X[i+1]*Y[i]);
  }
  if ( area > 0 ) puts("ccw");
  else puts("cw");
  return 0;
}