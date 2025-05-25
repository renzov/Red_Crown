#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const int MAXN = 500005;

bool used[MAXN];
int S[MAXN];

int main(){
	int N;

	scanf("%d", &N);
	for ( int i = 0; i < N; ++i )
		scanf("%d", S + i );
	
	sort( S, S + N );

	int l = N / 2 - 1;
	int r = N - 1;
	int ans = 0;
	while ( l >= 0 && 2*r >= N ){
		while ( l >= 0 && ( 2*S[l] > S[r] || used[l] ) ) l--;
		
		if ( l >= 0 )
			used[l] = used[r] = true, ans++;

		while ( r >= 0 && used[r] ) r--;
	}
	printf("%d\n", N - ans);
	return 0;
}
