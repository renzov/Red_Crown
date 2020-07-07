#include<cstdio>
#include<algorithm>
using namespace std;
const int MOD = 1000000007;
const int MAXN = 100005;
int P[MAXN];

void process(){
	int N;

	scanf("%d", &N);
	for ( int i=0; i < N; ++i )
		scanf("%d", P + i);

	sort( P, P + N );
	reverse( P, P + N );

	int res = 0;

	for ( int i=0; i < N; ++i ){
		res += max( 0, P[i] - i );
		res %= MOD;
	}
	printf("%d\n", res);
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}
