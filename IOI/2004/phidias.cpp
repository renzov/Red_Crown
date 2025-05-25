#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXL = 605;
const int MAXN = 205;

int dp[MAXL][MAXL];
int X[MAXN], Y[MAXN];

// dp[i][j] = min area leftover of a rectangle of width i and height j
// obs: we can always suppose that the top left corner is occupied by a piece

int main(){
	int W, H, N;

	scanf("%d %d %d", &W, &H, &N);
	for ( int i = 0; i < N; ++i )
		scanf("%d %d", X + i, Y + i );
	
	for ( int i = 0; i <= W; ++i )
		dp[i][0] = 0;
	for ( int j = 0; j <= H; ++j )
		dp[0][j] = 0;

	for ( int i = 1; i <= W; ++i ){
		for ( int j = 1; j <= H; ++j ){
			dp[i][j] = i * j;
			for ( int k = 0; k < N; ++k ){
				if ( X[k] <= i && Y[k] <= j ){
					// vertical cut
					dp[i][j] = min( dp[i][j], dp[ i - X[k] ][j] + dp[ X[k] ][ j - Y[k] ] );
					// horizontal cut
					dp[i][j] = min( dp[i][j], dp[i][ j - Y[k] ] + dp[ i - X[k] ][ Y[k] ] );
				}
			}
		}
	}
	printf("%d\n", dp[W][H]);
	return 0;
}

