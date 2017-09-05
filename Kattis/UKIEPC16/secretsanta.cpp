#include<cstdio>
#include<cmath>
using namespace std;

int main(){
	long long N;
	int dag[15];
	int fac[15];

	scanf("%lld", &N);	
	dag[0] = 1;
	dag[1] = 0;
	fac[0] = 1;
	fac[1] = 1;

	for ( int i=2; i <= 10; ++i ){
		dag[i] = ( i - 1 )*( dag[i-1] + dag[i-2] );
		fac[i] = i*fac[i-1];	
	}

	if ( N <= 10 ) printf("%f\n", 1 - (double)dag[N]/fac[N]);
	else printf("%f\n", 1 - 1/M_E);
	return 0;
}
