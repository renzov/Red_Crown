#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN = 100005;
const int FIRST = (1 << 20) - 1;
char S[MAXN];
int P[MAXN];
int C[MAXN];
int N;

long long tup[MAXN];

inline long long pack( const long long &hi, const long long &lo, const int &idx ){
	return (hi << 40LL) | (lo << 20LL) | idx;
}

int main(){
	// Read and add $
	scanf("%s", S);
	N = strlen(S);
	S[N++] = '$';

	// Fase 0
	for ( int i=0; i < N; ++i )
		tup[i] = pack( (S[i] - 'a'), 0LL, i );
	sort( tup, tup + N );
	for ( int i=0; i < N; ++i )
		P[i] = (int)(tup[i] & FIRST); 
	
	C[ P[0] ] = 0;
	for ( int i=1; i < N; ++i ){
		C[ P[i] ] = C[ P[i - 1] ];
		if ( (tup[i] >> 20LL) != (tup[i - 1] >> 20LL) ){
			C[ P[i] ]++;
		}
	}
	// Remaining phases
	for ( int k=0; (1 << k) < N ; k++ ){
		// creating new classes
		for ( int i=0; i < N; ++i )
			tup[i] = pack( C[i], C[(i + (1 << k))%N], i );
		sort( tup, tup + N );
		for ( int i=0; i < N; ++i ) 
			P[i] = (int)(tup[i] & FIRST);
		C[ P[0] ] = 0;
		for ( int i=1; i < N; ++i ){
			C[ P[i] ] = C[ P[i - 1] ];
			if ( (tup[i] >> 20LL) != (tup[i - 1] >> 20LL) ){
				C[ P[i] ]++;
			}
		}
	}
	for ( int i=0; i < N; ++i ){
		if (i) putchar(' ');
		printf("%d", P[i]);
	}
	puts("");
	return 0;
}
