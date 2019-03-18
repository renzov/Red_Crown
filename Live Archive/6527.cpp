#include<cstdio>
#include<cassert>
using namespace std;
long long f[64] = {0};

long long find_ones( const long long &X ){
	long long res = 0;
	int ones = 0; 
	for ( int i=63; i >= 0; --i ){
		if ( (X >> i) & 1 ){
			ones++;
			res += f[i];
			res += ( 1LL << i )*(ones - 1);
		}
	}
	return res + ones;
} 

int main(){
	// precalc number of ones in the numbers with i bits.
	f[1] = 1;
	for ( int i=2; i < 63; ++i )
		f[i] = (f[i - 1] << 1LL) + (1LL << (i-1));

	long long A, B;
	while ( scanf("%lld %lld", &A, &B) == 2 ){
		printf("%lld\n", find_ones( B ) - find_ones(A - 1)); 
	}
	return 0;
}
