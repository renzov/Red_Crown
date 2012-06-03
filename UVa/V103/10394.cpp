#include<cstdio>
const int SIZE = 20000000/2/8+1;
char mark[SIZE] = {0};
int res[200001];
int sieve(){
  long long i,j;
  for (i=3; i*i < 20000000; i+=2){
		if ((mark[i>>4] & (1<<((i>>1)&7))) == 0){
			for (j=i*i; j < 20000000; j+= i<<1) mark[j>>4] |= (1<<((j>>1)&7)); 
		}
  }
  int n = 0;
  int last = 2;
  for (i=3; i < 20000000; i+=2){
		if ((mark[i>>4]&(1<<((i>>1)&7))) == 0){ 
			 if ((i-last) == 2) res[n++] = last;
			 last = i;
		}
  }
}
int main(){
  int n;
  sieve();
  while (scanf("%d",&n) != EOF){
		printf("(%d, %d)\n",res[n-1],res[n-1] + 2);
  }
  return 0;
}