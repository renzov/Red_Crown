#include<cstdio>
#include<cmath>

bool noprime[50000] = {0};
int primes[50000];
int n;

void sieve(){
	 n = 0;
	 int i,j;
	 for (i=2; i < 46350; ++i){
		if (!noprime[i]){ 
		  primes[n++] = i; 
		  for (j=i+i; j < 46350; j+=i){
				noprime[j] = true;
		  }
		}
	 }
}


int main(){
  int x;
  bool first;
  int p;
  int r;
  sieve();
  while (scanf("%d",&x) && x){
		first = true;
		printf("%d = ",x);
		if (x < 0){ printf("-1"); first = false; x*=-1; }
		p = 0;
		r = (int)sqrt((double)x);
		//printf("WA\n");
		while (x > 1 && primes[p] <= r ){
		  //printf("WI\n");
		  while ((x % primes[p]) == 0){
				if (!first){ printf(" x "); }
				printf("%d",primes[p]); x /= primes[p]; 
				first = false;
		  }
		  p++;
		}
		if ( x > 1 ){
			 if (!first){ printf(" x "); }
			 printf("%d",x);
		}
		putchar('\n');
  }
  return 0;
}