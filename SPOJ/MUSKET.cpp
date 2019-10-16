#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 128;
int N;
bool W[MAXN][MAXN];		// W[i][j] = true iff i can beat j
int memo[MAXN][MAXN];	// memo[i][j] = i and j can beat every adversary from i + 1 ... j - 1
int ans[MAXN];			// vertices that can win the tournament

int solve( const int &a, const int &b ){
	if ( a == b || (a + 1)%N == b ) return 1;
	if ( memo[a][b] != -1 ) return memo[a][b];
	
	for ( int i=(a+1)%N; i != b; i=(i+1)%N ){
		if ( !W[a][i] && !W[b][i] ) continue;
		// W[a][i] == 1 or W[b][i] == 1
		if ( solve( a , i ) && solve( i , b ) ){
			return memo[a][b] = 1;
		}
	}
	return memo[a][b] = 0;
}

void process(){
	char s[MAXN];

	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%s", s);
		for ( int j=0; j < N; ++j )
			W[i][j] = ( s[j] == '1' );	
		fill( memo[i], memo[i] + N, -1 );
	}
	
	int res = 0;
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < N; ++j )
			if ( i != j && W[i][j] && solve( i , j ) && solve( j , i ) ){
				ans[res++] = i + 1; 
				break;
			}
	
	printf("%d\n", res);
	for ( int i=0; i < res; ++i ) printf("%d\n", ans[i]);
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}
