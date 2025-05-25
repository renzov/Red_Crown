#include<cstdio>
using namespace std;

const int MAXN = 2 * 50005;
bool opp[MAXN];

int main(){
	freopen("highcard.in", "r", stdin );
	freopen("highcard.out", "w", stdout );
	
	int N, idx;

	scanf("%d", &N);
	for ( int i = 0; i < N; ++i ){
		scanf("%d", &idx);
		idx--;
		opp[idx] = true;
	}

	int cnt = 0;
	int ans = 0;

	for ( int i = 0; i < 2*N; ++i ){
		if ( opp[i] ){
			cnt++;
		}
		else if ( cnt ){
			cnt--;
			ans++;
		}
	}
	printf("%d\n", ans );
	return 0;
}
