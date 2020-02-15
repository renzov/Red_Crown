// AC in Uva - WA in Live Archive
#include<cstdio>
#include<cstring>
#include<climits>
#include<algorithm>
using namespace std;

const int MAXN = 128;
const int MAXC = 10000;
int L[MAXN][MAXN];
double dp[128][MAXC + 5]; 	// dp[i][j] = prob. of a length i path has cost exactly j
double res[128][MAXC + 5];	// res[i][j] = prob. of a length i path has cost at most j
int cases = 0;

void process(){
	int N, R;
	char c;
	cases++;
	scanf("%d %d", &N, &R);
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < N; ++j ){
			scanf(" %c", &c);
			if ( i == j ) L[i][j] = 0;
			else L[i][j] = ( c == 'Y' )? 1:INT_MAX;
		}
	// floyd warshall
	for ( int k=0; k < N; ++k )
		for ( int i=0; i < N; ++i )
			for ( int j=0; j < N; ++j )
				if ( L[i][k] < INT_MAX && L[k][j] < INT_MAX )
					L[i][j] = min( L[i][j], L[i][k] + L[k][j] );
	

	memset( dp, 0, sizeof(dp) );
	dp[0][0] = 1.0;
	for ( int i=0; i < N; ++i )
		for ( int j=0; j <= MAXC; ++j ){
			if ( dp[i][j] == 0 ) continue;
			for ( int r=1; r <= R && j + r <= MAXC; ++r )
				dp[i + 1][ j + r ] += dp[ i ][ j ] / R;
		}

	for ( int i=0; i < N; ++i ){
		res[i][0] = dp[i][0];
		for ( int j=1; j <= MAXC; ++j )
			res[i][j] = res[i][j-1] + dp[i][j];
	}

	printf("Case %d\n", cases);
	int Q, u, v, d, m;
	scanf("%d", &Q);
	while ( Q-- ){
		scanf("%d %d %d", &u, &v, &m);
		u--, v--;
		d = L[u][v];
		printf("%.6f\n", (d < INT_MAX)? res[d][m]:0.0 );
	}
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- ){
		process();
		puts("");
	}
	return 0;
}
