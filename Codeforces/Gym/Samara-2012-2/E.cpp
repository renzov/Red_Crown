#include<cstdio>
using namespace std;

int main(){
	int P, Q;
	double p, q;
	scanf("%d %d", &P, &Q);
	
	p = (double)P/100.0;
	q = (double)Q/100.0;

	// Bayes rule
	
	// A = We get head in the second coin
	// B = We get head in the first coin

	// P(B) = 1/2 * p + 1/2 * q -- 1/2 = prob of choosing one of the coins. 
	// P( A \cap B ) = 1/2 * p * p + 1/2 * q * q

	double PB = 0.5 * ( p + q );
	double PAB = 0.5 * ( p * p + q * q );
	printf("%.12f\n", PAB / PB );
	return 0;
}
