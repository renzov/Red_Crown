#include<cstdio>
#include<cassert>
#include<cstring>
using namespace std;

long long gcd( long long a, long long b ){
	if ( a < b ) return gcd( b , a );
	if ( b == 0 ) return a;
	return gcd( b, a % b );
}

int main(){
	char S[63];
	int d;
	int pos;
	long long nines[15];
	long long pow10[15];
	// precalc powers of 10 and (9)^*
	nines[0] = 0;
	pow10[0] = 1;
	for ( int i=1; i < 15; ++i ){
		nines[i] = nines[i - 1] * 10 + 9;
		pow10[i] = pow10[i - 1] * 10;
	}
	// Read Input
	scanf("%s %d", S, &d);
	if ( S[1] == '.' ){
		pos = 2;
	}
	else if ( S[2] == '.' ){
		pos = 3;
	}
	else {
		assert( S[3] == '.' );
		pos = 4;
	}
	// get the length of decimal part
	int lenReal = strlen( S ) - pos;
	long long intPart, realPart;
	long long nonRep;
	S[pos - 1] = '\0';
	sscanf( S, "%lld", &intPart);
	sscanf( S + pos, "%lld", &realPart);
	// get the nonrepeating part
	if ( lenReal > d ){
		S[pos + lenReal - d] = '\0';
		sscanf( S + pos, "%lld", &nonRep);
	}
	else {
		nonRep = 0;
	}
	// Calculate the answer
	long long num = realPart - nonRep;
	long long den = nines[ d ] * pow10[ lenReal - d ];
	long long g = gcd( num , den );

	num /= g;
	den /= g; 

	num += ( den * intPart );
	g =  gcd( num , den );
	
	num /= g;
	den /= g; 
	
	printf("%lld/%lld\n", num, den );
	return 0;
}
