#include<iostream>
#include<sstream>
#include<string>
#include<cmath>
#include<cstdio>

using namespace std;

int primes[3600];
bool noprime[32770] = {0};
int n;
int res[3600];
int frec[3600];

void sieve(){
  n = 0;
  int i,j;
  for (i=2; i <= 32767; ++i){
		if (!noprime[i]){
			 primes[n++] = i;
			 for (j=i+i; j <= 32767; j+=i) noprime[j] = true;
		}
  }
}

int fast_pow(int x,int y){
  if (y==0) return 1;
  else if (y%2) return fast_pow(x,y-1)*x;
  else {  
	 int tmp = fast_pow(x,y/2);
	 return tmp*tmp;
  }
}

int main(){
  sieve();
  int m;
  int num;
  int r;
  int base,pot;
  int p;
  
  string line;
  while (1){
	 getline(cin,line);
	 stringstream in(line);
	 in >> base;
	 if (base == 0) break;
	 in >> pot;
	 num = fast_pow(base,pot);
	 while (in >> base >> pot){
		  num *= fast_pow(base,pot);
	 }
	 num--;
	 r = (int)sqrt((double)num);
	 p = 0;
	 m = 0;
	 while (num > 1 && primes[p] <= r){
		if (num % primes[p] == 0){ 
		  frec[m] = 0;
		  res[m] = primes[p];
		  while ( num % primes[p] == 0){ frec[m]++; num /= primes[p]; }
		  m++;
		}
		p++;
	 }
	 if (num > 1){
		frec[m] = 1;
		res[m] =  num;
		m++;
	 }
	 bool first = true;
	 for (int i=m-1; i >= 0; --i){
		if (!first) putchar(' ');
		printf("%d %d",res[i],frec[i]);
		first = false; 
	 }
	 putchar('\n');
  }

  return 0;
}
