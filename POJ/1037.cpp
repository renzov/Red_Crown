#include<cstdio>
using namespace std;
const int MAXN = 32;
long long cnt[MAXN][MAXN][2];	// cnt[i][j][dir] = # of i-permutations beginning in j and going dir
int rep[MAXN];
void process(){
	int N;
	long long K;

	scanf("%d %lld", &N, &K);

	// Init for base case
	cnt[1][1][1] = cnt[1][1][0] = 1LL;
	for ( int i=2; i <= N; ++i ){
		cnt[1][i][0] = 0;
		cnt[i][i][1] = 0;
	}
	
	for ( int n=2; n <= N; ++n ){
		for ( int i=1; i <= n; ++i ){
			if ( i > 1 )
				cnt[n][i][0] = cnt[n][i - 1][0] + cnt[n - 1][i - 1][1];
			if ( i < N )
				cnt[n][i][1] = cnt[n][i + 1][1] + cnt[n - 1][i][0];
		}
	}

	for ( int i=1; i <= N; ++i ) rep[i] = i;

	int last = -1;
	int dir;
	int ans[MAXN];

	for ( int i=1; i <= N && last < 1; ++i ){
		for ( int j=0; j < 1 && last < 1; ++j ){
			if ( cnt[N][i][j] >= K ){
				ans[1] = rep[i];
				last = i;
				dir = j;
			}
			K -= cnt[N][i][j];
		}
	}

	for ( int i=last; i < N; ++i ) rep[i] = i + 1;
	for ( int n=N - 1; n > 1; --n ){
		if ( dir ){	// going up
			for ( int i = last; i <= n; ++i ){

			}
		}
		else {	// going up
			for ( int i=1; i < last; ++i ){

			}
		}
	}
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- ) process();
	return 0;
}
