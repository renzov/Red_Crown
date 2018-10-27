#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 505;
int M[MAXN][MAXN];
int T[MAXN][MAXN];
long long SM[MAXN][MAXN] = {0};
long long ST[MAXN][MAXN] = {0};

inline long long sum( long long mat[MAXN][MAXN], const int &r1, const int &r2, const int &c1, const int &c2 ){
	return mat[r2][c2] - mat[r2][c1 - 1] - mat[r1 - 1][c2] + mat[r1 - 1][c1 - 1];
}

void calculate_sum( int mat[MAXN][MAXN], const int &r, const int &c, long long S[MAXN][MAXN] ){
	for ( int i=1; i <= r; ++i )
		for ( int j=1; j <= c; ++j )
			S[i][j] = mat[i][j] + S[i][j - 1] + S[i - 1][j] - S[i-1][j-1];
}

long long query( long long S[MAXN][MAXN], const int &r1, const int &r2, const int &c1, const int &c2 ){
	if ( r1 == r2 ) return 0LL;
	long long total = 0;
	for ( int i=r1 + 1; i <= r2; ++i ){
		total += sum( S, r1, i - 1, c1, c2 );
	}
	long long res = total;
	for ( int i=r2 - 1; i >= r1; i-- ){
		total -= sum( S, r1, i, c1, c2 );
		total += sum( S, i + 1, r2, c1, c2 );
		res = min( res , total );
	}
	return res;
}

void process(){
	int R, C, Q;
	scanf("%d %d %d", &R, &C, &Q);
	for ( int i=1; i <= R; ++i ){
		for ( int j=1; j <= C; ++j ){
			scanf("%d", &M[i][j]);
			T[j][i] = M[i][j];
		}
	}
	calculate_sum( M, R, C, SM );
	calculate_sum( T, C, R, ST );
	long long res;
	int r1, r2, c1, c2;
	for ( int i=1; i <= Q; ++i ){
		scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
		res = query( SM , r1, r2, c1, c2 ) + query( ST, c1, c2, r1, r2 );
		printf("%d %lld\n", i, res);
	}
}

int main(){
	int runs;
	scanf("%d", &runs);
	for ( int i=1; i <= runs; ++i ){
		printf("Test Case %d:\n", i);
		process();
		puts("");
	}
	return 0;
}
