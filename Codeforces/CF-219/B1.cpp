#include<cstdio>
using namespace std;
const int MAXN = 42;

int N, M;
char S[MAXN][MAXN];
int zero[MAXN][MAXN][MAXN][MAXN];
int cnt[MAXN][MAXN][MAXN][MAXN];

inline int val( int i, int i2, int j, int j2 ){
	return ( i <= i2 && j <= j2 )? cnt[i][i2][j][j2]:0;
}

void precalc_base(){
	// 1 x 1
	for ( int i = 0; i < N; ++i )
		for ( int j = 0; j < M; ++j )
			cnt[i][i][j][j] = zero[i][i][j][j] = ( S[i][j] == '0' )? 1:0;
	// 1 x 2
	for ( int i = 0; i < N; ++i )
		for ( int j = 1; j < M; ++j ){
			zero[i][i][j - 1][j] = ( zero[i][i][j-1][j-1] && zero[i][i][j][j] )? 1:0;
			cnt[i][i][j - 1][j] = cnt[i][i][j-1][j-1] + cnt[i][i][j][j] + zero[i][i][j-1][j];
		}
	// 1 x X - X >= 3
	int k;
	for ( int i = 0; i < N; ++i )
		for ( int len = 3; len <= M; ++len )
			for ( int j = 0; (j + len - 1) < M; ++j ){
				k = j + len - 1;
				zero[i][i][j][k] = (zero[i][i][j][k - 1] && (S[i][k] == '0') )? 1:0;
				cnt[i][i][j][k] = cnt[i][i][j][k - 1] + cnt[i][i][j + 1][k] - cnt[i][i][j + 1][k - 1] + zero[i][i][j][k];
			}
	// 2 x 1
	for ( int j = 0; j < M; ++j )
		for ( int i = 1; i < N; ++i ){
			zero[i - 1][i][j][j] = ( zero[i-1][i-1][j][j] && zero[i][i][j][j] )? 1:0;
			cnt[i-1][i][j][j] = cnt[i-1][i-1][j][j] + cnt[i][i][j][j] + zero[i-1][i][j][j];
		}
	
	// X x 1 - X >= 3
	for ( int j = 0; j < M; ++j )
		for ( int len = 3; len <= N; ++len )
			for ( int i = 0; (i + len - 1) < N; ++i ){
				k = i + len - 1;
				zero[i][k][j][j] = (zero[i][k - 1][j][j] && (S[k][j] == '0'))? 1:0;
				cnt[i][k][j][j] = cnt[i][k-1][j][j] + cnt[i+1][k][j][j] - cnt[i+1][k-1][j][j] + zero[i][k][j][j];
			}
}

void precalc_gen(){
	for ( int l = 2; l <= N; ++l )
		for ( int w = 2; w <= M; ++w ){
			for ( int i = 0; (i + l - 1) < N; ++i )
				for ( int j = 0; (j + w - 1) < M; ++j ){
					int i2 = i + l - 1;
					int j2 = j + w - 1;
					zero[i][i2][j][j2] = ( zero[i][i2 - 1][j][j2] && zero[i][i2][j][j2 - 1] && (S[i2][j2] == '0') )? 1:0;	
					cnt[i][i2][j][j2] = val(i, i2, j, j2 - 1) + val(i, i2, j + 1, j2) + val(i, i2 - 1, j, j2) + val(i + 1, i2, j, j2) 
										- val(i, i2, j + 1, j2 - 1) - val(i + 1, i2 - 1, j, j2) - val(i + 1, i2, j + 1, j2) 
										- val(i + 1, i2, j, j2 - 1) - val(i, i2 - 1, j + 1, j2) - val(i, i2 - 1, j, j2 - 1)
										+ val(i, i2 - 1, j + 1, j2 - 1) + val(i + 1, i2, j + 1, j2 - 1) + val(i + 1, i2 - 1, j, j2 - 1) 
										+ val(i + 1, i2 - 1, j + 1, j2) - val(i + 1, i2 - 1, j + 1, j2 - 1) + zero[i][i2][j][j2];
				}
		}
}

int main(){
	int Q;

	scanf("%d %d %d", &N, &M, &Q);
	for ( int i = 0; i < N; ++i )
		scanf("%s", S[i]);
	
	precalc_base();
	precalc_gen();
	
	int a, b, c, d;
	while (Q--){
		scanf("%d %d %d %d", &a, &b, &c, &d);
		a--, b--, c--, d--;
		printf("%d\n", cnt[a][c][b][d]);
	}

	return 0;
}
