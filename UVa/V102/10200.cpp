#include<cstdio>
#include<cmath>

bool noprime[100010045] = {0};
int parc[10005] = {0};

void sieve(){
	int i,j;
	int r = sqrt(100010041);
	for(i=2; i <= r; ++i){
		  if (!noprime[i]){
				for (j=i+i; j <= 100010041; j+=i) noprime[j] = true;
		  }
	} 
	parc[0] = 1;
	for (i=1; i <= 10000; ++i){
		parc[i] = parc[i-1];
		if (!noprime[i*i + i + 41]) parc[i]++;
   }
}

int main(){
  sieve();
  int a,b;
  int c1;
  double res;
  while (scanf("%d %d",&a,&b) != EOF){
		c1 = ( a > 0 )? (parc[b] - parc[a-1]) : parc[b];
		res = (double)c1*100.0/(b-a+1);
		res = floor(res*100 + .5)/100;
		printf("%0.2lf\n",res);
	 
  } 
  return 0;
}