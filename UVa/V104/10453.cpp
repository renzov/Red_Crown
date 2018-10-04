#include<queue>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 1024;

int op[MAXN][MAXN];
int dp[MAXN][MAXN];
char S[MAXN];
deque<char> d;

void build( const int &l, const int &r ){
	if ( op[l][r] == 0 ){ 
		if ( l <= r ) d.push_front( S[l] );	
		return;
	}
	if ( op[l][r] == 1 ){
		build( l + 1 , r );
		d.push_front( S[l] ); d.push_back( S[l] );
	}
	else if ( op[l][r] == 2 ){
		build( l , r - 1 );
		d.push_front( S[r] ); d.push_back( S[r] );
	}
	else {
		build( l + 1 , r - 1 );
		d.push_front( S[l] ); d.push_back( S[l] );	
	} 
}
int main(){
	int N;
	int j;
	
	while ( scanf("%s", S) != EOF ){
		N = strlen(S);
		for ( int i=0; i < N; ++i )
			for (int j = 0; j < N; ++j )
				dp[i][j] = op[i][j] = 0;
		
		for ( int k=1; k < N; ++k ){
			for ( int i=0; i + k < N; ++i ){
				j = i + k;
				// Fix the left character
				dp[i][j] = 1 + dp[i + 1][j]; op[i][j] = 1; 
				// Fix the right character
				if ( dp[i][j] > dp[i][j - 1] + 1 ){
					dp[i][j] = 1 + dp[i][j - 1]; op[i][j] = 2;
				} 
				// If border is the same
				if ( S[i] == S[j] && dp[i][j] > dp[i + 1][j - 1] ){
					dp[i][j] = dp[i + 1][j - 1]; op[i][j] = 3;
				}
			}
		}
		build( 0 , N - 1 );
		printf("%d ", dp[0][N-1]);
		while ( !d.empty() ){
			putchar( d.front() );
			d.pop_front();
		}
		puts("");
	}
	return 0;
}
