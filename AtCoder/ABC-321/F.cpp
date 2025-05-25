#include<cstdio>
using namespace std;
const int MAXK = 5005;
const int MOD = 998244353;

long long cnt[MAXK];

int main(){
	int Q, K;
	char op;
	int x;

	scanf("%d %d", &Q, &K);
	cnt[0] = 1;

	while ( Q-- ){
		scanf(" %c %d", &op, &x);
		if ( op == '+' ){
			for ( int i = K; i >= x; --i ){
				cnt[i] += cnt[i - x];
				cnt[i] %= MOD;
			}
		}
		else {
			for ( int i = x; i <= K; ++i ){
				cnt[i] += ( MOD - cnt[i - x] );
				cnt[i] %= MOD;
			}
		}
		printf("%lld\n", cnt[K]);
	}

	return 0;
}
