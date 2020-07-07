#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 2005;
int N, H, L, R;
int dp[2][MAXN];
int A[MAXN];

int main(){
	scanf("%d %d %d %d", &N, &H, &L, &R);
	for ( int i=0; i < N; ++i )
		scanf("%d", A + i);
	
	
	int act = 1, prev = 0;
	int nxt;	
	for ( int i=N - 1; i >= 0; --i ){		
		for ( int j=0; j < H; ++j ){
			nxt = j + A[i];
			if ( nxt >= H ) nxt -= H;
			dp[act][j] = dp[prev][nxt] + ( nxt >= L && nxt <= R );
			nxt = j + A[i] - 1;
			if ( nxt >= H ) nxt -= H;
			dp[act][j] = max( dp[act][j], dp[prev][nxt] + ( nxt >= L && nxt <= R ));
		}
		swap( act, prev );
	}
	printf("%d\n", dp[prev][0]);
	return 0;
}
