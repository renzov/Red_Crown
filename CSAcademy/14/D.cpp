#include<cstdio>
using namespace std;
const int MOD = 1000000000 + 7;
const int MAXN = 100005;

int X[MAXN];
int S[MAXN] = {0};

int main(){
	int N, A, B;

	scanf("%d %d %d", &N, &A, &B);
	for ( int i=1; i <= N; ++i )
		scanf("%d", X + i );
	
	long long res = 0;
	long long cnt[2];
	
	for ( int bit=0; bit < 30; ++bit ){
		// Calculate the partial sum of the i-th bit
		cnt[0] = cnt[1] = 0;
		for ( int i=1; i <= N; ++i )
			S[i] = S[ i - 1 ] ^ ((X[i] >> bit)&1);
		
		for ( int j=1; j <= N; ++j ){
			if ( j - B > 0 ){
				cnt[ S[j - B - 1] ]--;
			}
			if ( j - A >= 0 ){
				cnt[ S[j - A] ]++;
			}
			res += ((1 << bit) * cnt[1 ^ S[j]]);
			res %= MOD;
		}
	}
	printf("%lld\n", res);
	return 0;
}
