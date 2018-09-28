#include<cstdio>
#include<algorithm>
using namespace std;

int N[65];
long long C[65][65] = {0};

void precalc(){
	N[0] = 0;
	N[1] = 0;
	int b;
	for ( int i=2; i < 64; ++i ){
		b = __builtin_popcount(i);
		N[i] = N[b] + 1;
	}
	
	for ( int i=0; i < 64; ++i )
		C[i][1] = i;
	
	for ( int i=1; i < 64; ++i )
		for ( int j=2; j < 64; ++j )
			C[i][j] = C[i - 1][j - 1] + C[i - 1][ j ]; 	
	
	
	for ( int i=0; i < 64; ++i )
		C[i][1]++;
}

long long get_total( long long X, int K ){
	long long T[65];
	int cnt = 0;
	
	if ( X < 2 ) return 0;
	
	fill( T, T + 64, 0 );
	for ( int pos=63; pos >= 0; pos-- ){
		if ( (X >> pos) & 1 ){
			for ( int i=63; i >= cnt; i-- ){
				T[i] += C[pos][i-cnt];
			}		
			cnt++;
		}
	}
	long long res = 0;
	for ( int i=0; i < 63; ++i ){
		if ( N[i] + 1 == K ) res += T[i];
	}
	return res;
}

int main(){
	long long L, R;
	int K;
	long long res;
	
	precalc();
	while ( scanf("%lld %lld %d", &L, &R, &K ) && (L + R + K) ){
		if ( K == 0 ){
			printf("%d\n", L > 1? 0:1 );
			continue;
		}
		// K > 0
		res = get_total( R , K ) - get_total( L - 1 , K );
		if ( L == 1 && K == 1 && R != 1 ) res--;
		printf("%lld\n", res);
	}
	return 0;
}
