#include<cstdio>
#include<algorithm>
using namespace std;

int max2x2[4] = { 0, 5, 3, 1 };
int P[10];

void process(){
	// Packing 6 x 6
	int res = P[6];
	// Packing 5 x 5
	int maxOnes = P[5] * 11;
	res += P[5];
	P[1] -= min( P[1], maxOnes );
	// Packing 4 x 4
	int maxTwo = P[4] * 5;
	res += P[4];
	if ( maxTwo <= P[2] ){
		P[2] -= maxTwo;
	}
	else {
		maxOnes = (20 * P[4]) - (4 * P[2]);
		P[2] = 0;
		P[1] -= min( P[1], maxOnes );
	}
	// Packing 3 x 3
	res += (P[3] / 4);
	P[3] %= 4;
	if ( P[3] ){ // Speacial case
		maxTwo = min( P[2], max2x2[ P[3] ] );
		P[2] -= maxTwo;
		maxOnes = 36  - (P[3] * 9) - maxTwo * 4;
		P[1] -= min( P[1], maxOnes );
		res++;
	}
	// Packing 2 x 2
	res += (P[2] / 9);
	P[2] %= 9;
	if ( P[2] ){
		res++;
		P[1] -= min( P[1], 36 - P[2]*4 );
	}
	// Packing 1 x 1
	res += (P[1] / 36);
	P[1] %= 36;
	if ( P[1] )
		res++;
	printf("%d\n", res);
}

int main(){
	int sum;
	while ( 1 ){
		sum = 0; 
		for ( int i=1; i <= 6; ++i ){
			scanf("%d", P + i );
			sum += P[i];	
		}
		if ( sum ) process();
		else break;
	}
	return 0;
}
