#include<cstdio>
using namespace std;
const int MAXB = 130;
const int MAXK = 1024;
const int MOD = 1000000009;

int p[MAXB];
long long pref[MAXB][MAXK];
long long suff[MAXB][MAXK];

int main(){
	int K, B;

	scanf("%d %d", &K, &B);
	
	p[0] = 1;
	for ( int i=1; i < B; ++i ){
		p[i] = 2 * p[i - 1];
		p[i] %= K;
	}
	// Count the number of prefixes of size i with mod j (0 ... B - 1)
	pref[0][0]++;
	pref[0][1 % K]++;
	int nxt;

	for ( int i=0; i < B - 1; ++i ){
		for ( int j=0; j < K; ++j )
			if ( pref[i][j] > 0 ){
				// put a zero in pos i + 1
				pref[i + 1][j] += pref[i][j];
				pref[i + 1][j] %= MOD;
				// put a one in pos i + 1
				nxt = (p[i + 1] +  j) % K;
				pref[i + 1][nxt] += pref[i][j];
				pref[i + 1][nxt] %= MOD;
			}
	}
	// Count the number of suffixes of size i with mod j
	suff[B][0] = 1;
	suff[B - 1][0]++;
	suff[B -  1][ p[B - 1] ]++;
	for ( int i=B - 1; i > 0; --i ){
		for ( int j=0; j < K; ++j ){
			if ( suff[i][j] ){
				// put a zero in pos i - 1
				suff[i - 1][j] += suff[i][j];
				suff[i - 1][j] %= MOD;
				// put a one in pos i - 1
				nxt = (p[i - 1] + j) % K;
				suff[i - 1][nxt] += suff[i][j];
				suff[i - 1][nxt] %= MOD;
			}
		}
	}
	// Now, for each position count how many times a one appears
	long long res = suff[1][K - 1];	// number of multiples that has LSB equal to 1
	for ( int i=B - 1; i > 0; --i ){
		for ( int j=0; j < K; ++j ){
			if ( suff[i + 1][j] ){
				nxt = (j + p[i]) % K;
				nxt = (K - nxt) % K;
				res += suff[i + 1][j] * pref[i - 1][nxt];
				res %= MOD;
			}
		}
	}
	printf("%lld\n", res);
	return 0;
}
