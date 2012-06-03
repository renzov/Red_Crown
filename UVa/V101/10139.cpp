#include<cstdio>
#include<cmath>
bool noprime[1<<18] = {0};
int primes[1<<18];
int x;

void sieve(){
  x = 0;
  int i,j;
  int r = 1 << 16;
  for (i=2; i < r ; ++i){
		if (!noprime[i]){
			 primes[x++] = i;
			 for (j=i+i; j < r; j+=i){
				  noprime[j] = true;
			 }
		}
  }
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
  
  sieve();
  while (scanf("%d %d",&n,&m) != EOF){
		if (m==0) printf("%d does not divide %d!\n",m,n);
		else if (m==1) printf("%d divides %d!\n",m,n); 
		else if (n == 0 || n == 1) printf("%d does not divide %d!\n",m,n); 
		else {
			 /* factorize m */
			 r = sqrt(m);
			 p = 0;
			 t = m;
			 ok = true;
			 while (ok && t > 1 && primes[p] <= r){
				  if (t % primes[p] == 0){
						cnt = 0;
						while (t % primes[p] == 0){ t/= primes[p]; cnt++; }
						if (times(n,primes[p]) < cnt) ok = false;
				  }
				  ++p;
			 }
			 if (t > 1){
				  if (times(n,t) < 1) ok = false;
			 }
			 if (ok) printf("%d divides %d!\n",m,n);
			 else printf("%d does not divide %d!\n",m,n);
		}
  }
  return 0;
}