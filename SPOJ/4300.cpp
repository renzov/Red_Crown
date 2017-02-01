#include<cstdio>
int res[10005];
int sq(int x){
  int r = 1;
  for (int i=2; i*i <= x; ++i){
		if (x%i == 0) r++;
  }
  return r;
}
int main(){
  int n;
  res[1] = 1; res[2] = 2; res[3] = 3;
  scanf("%d",&n);
  for (int i=4; i <= n; ++i){
		res[i] = res[i-1] + sq(i);
  }
  printf("%d\n",res[n]);
  return 0;
}