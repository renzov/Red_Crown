#include<iostream>
#include<string>
using namespace std;

const int MAXN = 1024;

int dp[MAXN][MAXN];
string best[MAXN][MAXN];
string S;

void process(){
	
	int N, j;
	N = S.length();

	
	for ( int i=0; i < N; ++i )
		dp[i][i] = 1, best[i][i] = string( 1, S[i] );
	
	if ( N >= 2 ){
		for ( int i=0; i < N - 1; ++i ){
			if ( S[i] == S[i+1] ){
				dp[i][i + 1] = 2;
				best[i][i+1] = string( 2, S[i] );
			}
			else {
				dp[i][i + 1] = 1;
				best[i][i+1] = string( 1, min(S[i], S[i+1]) );
			}
		}
	}

	for ( int len=3; len <= N; ++len ){
		for ( int i=0; i + len <= N; ++i ){
			j = i + len - 1;
			if ( S[i] == S[j] ){
				dp[i][j] = dp[i+1][j-1] + 2;
				best[i][j] = S[i] + best[i+1][j-1] + S[j];
			}
			else {
				if ( dp[i+1][j] > dp[i][j-1] ){
					dp[i][j] = dp[i+1][j];
					best[i][j] = best[i+1][j];
				}
				else if (dp[i+1][j] < dp[i][j-1]){
					dp[i][j] = dp[i][j-1];
					best[i][j] = best[i][j-1];
				}
				else {
					dp[i][j] = dp[i+1][j];
					best[i][j] = min( best[i+1][j], best[i][j-1] );
				}
			}
		}
	}

	cout << best[0][N - 1] << "\n";
}

int main(){
	while ( cin >> S )
		process();
	return 0;
}
