#include<cstdio>
#include<climits>
#include<algorithm>
#include<cstdlib>
using namespace std;

typedef pair<int,int> pii;
typedef pair<int, pii> piii;

const int MAXN = 128;
piii G[MAXN];
int dp[MAXN];	// dp[i] = max prosperity choosing i at last

void process(){
	int N, K ,T;
	
	scanf("%d %d %d", &N, &K, &T);
	for ( int i=0; i < N; ++i ) scanf("%d", &G[i].first);
	for ( int i=0; i < N; ++i ) scanf("%d", &G[i].second.first);
	for ( int i=0; i < N; ++i ) scanf("%d", &G[i].second.second);

	sort( G, G + N );

	int s, t, p;
	for ( int i=0; i < N; ++i ){
		t = G[i].first, p = G[i].second.first, s = G[i].second.second;
		// Check if we can set it alone
		if ( s <= t ) dp[i] = p;
		else dp[i] = -INT_MAX;
	
		for ( int j=0; j < i; ++j ){
			if ( dp[j] > -INT_MAX && abs(s - G[j].second.second) <= (t - G[j].first) ){
				dp[i] = max( dp[i] , dp[j] + p );
			}
		}
	}
	printf("%d\n", max(0, *max_element(dp, dp + N)));
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- ){
		process();
		if ( runs ) puts("");
	}
	return 0;
}
