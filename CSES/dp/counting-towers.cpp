#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXT = 128;
const int MOD = 1000000007;
long long mat[8][8] = { {0, 1, 0, 1, 0, 0, 0, 0}, {0, 1, 1, 1, 0, 0, 0, 1}, {0, 1, 1, 1, 0, 0, 0, 1}, {0, 1, 0, 1, 1, 1, 1, 1}, 
{0, 1, 0, 1, 1, 1, 1, 1}, {0, 1, 0, 1, 1, 1, 1, 1}, {0, 1, 0, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0} };

int q[MAXT];
int idx[MAXT];
long long ans[MAXT];
long long dp[2][8];

void solve( const int &T ){
	int prev = 0;
	int act = 1;
	
	for ( int i = 0; i < 8; ++i )
		dp[prev][i] = mat[0][i];
	
	int i = 0;
	int len = 0;
	while ( i < T ){
		// increase len
		for ( int j = 1; j < 8; ++j ){
			dp[act][j] = 0;
			for ( int k = 0; k < 8; ++k ){
				if ( mat[k][j] ){
					dp[act][j] += dp[prev][k];
					dp[act][j] %= MOD;
				}
			}
		}
		act ^= 1;
		prev ^= 1;
		len++;
		while ( i < T && len == q[ idx[i] ] ){
			ans[ idx[i] ] = dp[prev][7];
			i++;
		}
	}
}

bool comp( const int &i, const int &j ){
	return q[i] < q[j];
}

int main(){
	int T;
	
	scanf("%d", &T);
	for ( int i = 0; i < T; ++i ){
		scanf("%d", q + i );
		idx[i] = i;
	}
	sort( idx, idx + T, comp );
	solve( T );
	for ( int i = 0; i < T; ++i )
		printf("%lld\n", ans[i]);
	return 0;
}
