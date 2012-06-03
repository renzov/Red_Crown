#include<cstdio>
#include<cmath>
const int SIZE = 1000000/2/8+2;
char mark[SIZE] = {0};
int primes[1000000];
int sieve(){
  long long i,j;
  for (i=3; i*i <= 1000000; i+=2){
		if ((mark[i>>4] & (1<<((i>>1)&7))) == 0){
			for (j=i*i; j <= 1000000; j+= i<<1) mark[j>>4] |= (1<<((j>>1)&7)); 
		}
  }
  int n = 0;
  primes[n++] = 2;
  for (i=3; i <= 1000000; i+=2){
		if ((mark[i>>4]&(1<<((i>>1)&7))) == 0){ 
			 primes[n++] = i;
		}
  }
}
int main(){
  int n;
  int r;
  int p;
  int res;
  int t;

  sieve();
  while (scanf("%d",&n) && n){
	 r = sqrt(n);
	 p = 0;
	 res = 0;
	 t = n;
	 //printf("Factors of %d\n",n);
	 while ( t>1 && primes[p] <= r ){
		  if (t % primes[p] == 0){ 
			 res++;
			 //printf("%d\n",primes[p]);
			 while (t % primes[p] == 0){ t /= primes[p]; } 
		  }
		  p++;
	 }
	 if (t > 1){ res++; } 
	 printf("%d : %d\n",n,res);
  }
  return 0;
}