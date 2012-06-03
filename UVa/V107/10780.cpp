#include<cstdio>
#include<cmath>
#include<climits>
const int SIZE = 5000/2/8+2;
char mark[SIZE] = {0};
int primes[5000];
int sieve(){
  long long i,j;
  for (i=3; i*i <= 5000; i+=2){
		if ((mark[i>>4] & (1<<((i>>1)&7))) == 0){
			for (j=i*i; j <= 5000; j+= i<<1) mark[j>>4] |= (1<<((j>>1)&7)); 
		}
  }
  int n = 0;
  primes[n++] = 2;
  for (i=3; i <= 5000; i+=2){
		if ((mark[i>>4]&(1<<((i>>1)&7))) == 0){ 
			 primes[n++] = i;
		}
  }
}
inline int min(int a,int b){
  return (a <= b)? a : b;
}
int times(int n,int p){
  int s = 0;
  while (n){ n/=p; s += n; }
  return s;
}
int main(){
  int p;
  int r;
  bool ok;
  int t;
  int cnt;
  int n,m;
  int runs;
  int cases = 0;
  int f;
  int minExp;
  sieve();
  scanf("%d",&runs);
  while (runs--){
		cases++;
		scanf("%d %d",&m,&n);
		if (n==1){
			 if (m > 1) printf("Case %d:\nImpossible to divide\n",cases);
			 else printf("Case %d:\n1\n",cases);
		}
		else {
			 /* factorize m */
			 r = sqrt(m);
			 p = 0;
			 t = m;
			 ok = true;
			 minExp = INT_MAX;
			 while (ok && t > 1){
				  if (t % primes[p] == 0){
						cnt = 0;
						while (t % primes[p] == 0){ t/= primes[p]; cnt++; }
						f = times(n,primes[p]);
						if (f < cnt) ok = false;
						else minExp = min(minExp,f/cnt);
				  }
				  ++p;
			 }
			 if (ok) printf("Case %d:\n%d\n",cases,minExp);
			 else printf("Case %d:\nImpossible to divide\n",cases);
		}
  }
  return 0;
}