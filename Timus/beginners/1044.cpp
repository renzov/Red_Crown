#include<cstdio>

int frec[ 100000 ] = {0};
int sum [ 100000 ] = {0};

int get_sum(int x){
  int r = 0;
  while (x){
	 r += (x % 10);
	 x /= 10;
  }
  return r;
}

int main(){
  int n;
  int bound = 1;
  scanf("%d",&n);
  n /= 2;
  for (int i=0; i < n; ++i) bound *= 10;
  for (int i=0; i < bound; ++i){
		sum[i] = get_sum(i);
		frec[sum[i]]++;
  }
  int res = 0;
  for (int i=0; i < bound; ++i)
	 res += frec[ sum[i] ];
  printf("%d\n",res);
  return 0;
}