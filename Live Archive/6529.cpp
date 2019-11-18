#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MOD = 1000000007;

int f[10];
long long C[128][128];
long long dp[10][11][11][128]; // dp[d][me][mo][x] = number of ways to obtain a number using digits d ... 9, such 
							   // that mod of the sum in even (resp. odd) positions is me (resp. mo) and we have x even positions 
							   // left. Note that odd positions is redundant in the state of the dp. It is completely determined by x

long long solve( const int &d, const int &even, const int &odd, const int &me, const int &mo ){
	if ( d == 10 ) return ( me == mo );
	if ( dp[d][me][mo][even] != -1 ) return dp[d][me][mo][even]; 
	
	long long &res = dp[d][me][mo][even];
	res = 0;	
	
	long long ways;
	int mod;
	for ( int i=0, j; i <= f[d]; ++i ){
		j = f[d] - i;
		if ( even < i || odd < j ) continue;
		ways = (C[even][i] * C[odd][j]) % MOD;
		ways *= solve( d + 1, even - i, odd - j, (me + d*i)%11, (mo + d*j)%11 );
		ways %= MOD;
		res += ways;
		res %= MOD;
	}
	return res;
}

void process( char *s ){
	fill( f, f + 10, 0 );
	for ( int i=0; s[i] ; ++i )
		f[ s[i]-'0' ]++;
	
	int N = strlen(s);
	int even = (N + 1) >> 1;
	int odd = N - even;

	long long res = 0;
	long long tmp;
	// force the first digit
	memset( dp, -1, sizeof(dp) );
	for ( int i=0;  i <= f[0]; ++i ){
		if ( i > even - 1 ) continue;
		tmp = C[even - 1][i] * C[odd][ f[0] - i ] % MOD;
		res += ( tmp * solve( 1, even - i, odd - ( f[0] - i ) , 0, 0 ) ) % MOD;
		res %= MOD;
	}
	printf("%lld\n", res);
}

int main(){
	char s[128];
	
	for ( int i=0; i <= 100; ++i ){
        C[i][0] = C[i][i] = 1;		
		for ( int k=1; k < i; ++k ){
			C[i][k] = C[i - 1][k - 1] + C[i - 1][k];
			C[i][k] %= MOD;
		}
	}

	while ( scanf("%s", s) != EOF )
		process(s);
	return 0;
}
