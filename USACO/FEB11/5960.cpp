#include<cstdio>
#include<cctype>
#include<vector>
#include<cstring>
using namespace std;
vector<int> T[60];
const int MOD = 97654321;
long long dp[56][256][256];
bool calc[56][256][256] = {0};

int toidx( const char &c ){
	return islower(c)? (c - 'a'):(c-'A'+26);
}

int U, L, P;

long long f( int last, int u, int l ){
	if ( u < 0 || l < 0 ) return 0;
	if ( u==0 && l==0 ) return 1;
	if ( calc[last][u][l] ) return dp[last][u][l];
	calc[last][u][l] = true;
	long long &ref = dp[last][u][l] = 0;
	for ( int j=0; j < (int)T[last].size(); ++j ){
		if ( T[last][j] < 26 )	ref += f( T[last][j], u, l - 1 );			
		else ref += f( T[last][j], u - 1, l );
		ref %= MOD;
	}
	return ref;
}

int main(){
	int u, v;
	char A,B;

	scanf("%d %d %d", &U, &L, &P);
	for (int i=0; i < P; ++i ){
		scanf(" %c %c", &A, &B);
		u = toidx( A );
		v = toidx( B );
		T[u].push_back(v);
	}
	int delta1, delta2;
	long long res = 0;
	for ( int i=0; i < 52; ++i ){

		if ( i < 26 ) delta1 = 0, delta2 = 1;
		else delta1 = 1, delta2 = 0;		

		for ( int j=0; j < (int)T[i].size(); ++j ){
			if ( T[i][j] < 26 )	res += f( T[i][j], U - delta1, L - delta2 - 1 );
			else res += f( T[i][j], U - delta1 - 1, L - delta2 );;
			res %= MOD;
		}
	}
	printf("%lld\n", res);
	return 0;
}
