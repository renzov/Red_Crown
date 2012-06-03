#include<cstdio>
using namespace std;
const int MAXN = 1000000;
bool nsp[1000001] = {0};
int p[ 500005 ];
void sieve(){
  int P;
  int i,j;
  p[0] = 2; P = 1;
  for ( i = 4; i <= MAXN; i+=2 ) nsp[i] = true;
  for ( i = 3; i <= MAXN; i += 2 ){
	 if ( !nsp[i] ){
		p[ P++ ] = i;
		for ( j = 2*i; j <= MAXN ; j += i ) nsp[j] = true;
	 }
  }
}

int main(){
  sieve();
  int n,i;
  bool f;
  while ( scanf("%d",&n) && n ){
	 printf("%d:\n",n); f = false;
	 for ( i = 0; p[i] <= (n>>1) && !f ; ++i ){
		if ( !nsp[ n - p[i] ] ){
		  printf("%d+%d\n",p[i],n-p[i]);
		  f = true;
		}
	 }
	 if ( !f ) puts("NO WAY!");
  }
  return 0;
}