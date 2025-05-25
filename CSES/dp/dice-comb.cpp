#include<cstdio>
using namespace std;
const int MAXN = 1000005;
const int MOD = 1000000007;

int cnt[MAXN];

int main(){
	int N;

	scanf("%d", &N);
	cnt[0] = 1;

	for ( int i = 1; i <= N; ++i )
		for ( int j = 1; j <= 6 && j <= i; ++j ){
			cnt[i] += cnt[i - j];
			cnt[i] %= MOD;	
		}
	printf("%d\n", cnt[N]);
	return 0;
}
