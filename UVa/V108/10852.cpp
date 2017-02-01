#include<cstdio>
#include<cmath>
#include<climits>
const int SIZE = 10000/2/8+2;
char mark[SIZE] = {0};
int primes[10000];
int n;
int sieve(){
  long long i,j;
  for (i=3; i*i <= 5000; i+=2){
		if ((mark[i>>4] & (1<<((i>>1)&7))) == 0){
			for (j=i*i; j <= 10000; j+= i<<1) mark[j>>4] |= (1<<((j>>1)&7)); 
		}
  }
  n = 0;
  primes[n++] = 2;
  for (i=3; i <= 10000; i+=2){
		if ((mark[i>>4]&(1<<((i>>1)&7))) == 0){ 
			 primes[n++] = i;
		}
  }
}
inline int max(int a,int b){
  return (a >= b)? a:b;
}
int main(){
  sieve();
  int runs;
  int m;
  int res;
  int p;
  scanf("%d",&runs);
  while (runs--){
		scanf("%d",&m);
		res = 0;
		p = 0;
		for (int i=0; i < n && primes[i] <= m; ++i){
			 if (m%primes[i] > res){ p = i; res = m%primes[i]; }
		}
		printf("%d\n",primes[p]);
  }
  return 0;
}