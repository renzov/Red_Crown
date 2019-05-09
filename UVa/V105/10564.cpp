#include<cstdio>
#include<cstring>
#include<algorithm>
#include<climits>
using namespace std;
const int MAXN = 22;
const int MAXS = 505;

int N, S;
int V[2*MAXN][MAXN];
long long cnt[2*MAXN][MAXN][MAXS] = {0};
int st[2*MAXN][MAXN][MAXS];
long long path[2*MAXN][MAXN][MAXS];

void process(){

	for ( int i=0; i < 2*MAXN; ++i )
		for ( int j=0; j < MAXN; ++j )
			for ( int k=0; k < MAXS; ++k ){
				st[i][j][k] = INT_MAX;
				cnt[i][j][k] = path[i][j][k] = 0;
			}

	for ( int i=0; i < N; ++i )
		for ( int j=0; j < N - i; ++j )
			scanf("%d", &V[i][j]);
	for ( int i=1; i < N; ++i )
		for ( int j=0; j <= i; ++j )
			scanf("%d", &V[N - 1 + i][j]);

	// Initialize the dp
	for ( int i=0; i < N; ++i ){
		cnt[0][i][ V[0][i] ] = 1;
		st[0][i][ V[0][i] ] = i;
	}
	
	int ns;
	long long np;

	for ( int i=0; i < N-1; ++i ){
		for ( int j=0; j < N - i; ++j ){
			for ( int s = 0; s <= S; ++s ){
				if ( cnt[i][j][s] ){
					ns = s + V[i+1][j];
					if ( ns <= S ){
						cnt[ i + 1 ][ j ][ ns ] += cnt[i][j][s];
						np = ( path[i][j][s] << 1LL) | 1LL; // Right path
						if ( st[i+1][j][ns] > st[i][j][s] ){
							st[ i + 1 ][ j ][ ns ] = st[i][j][s];
							path[ i + 1 ][ j ][ ns ] = np;
						}
						else if ( st[i+1][j][ns] == st[i][j][s] && np < path[i+1][j][ns] ){
							path[i+1][j][ns] = np;
						}
					}
					if ( j && (s + V[i+1][j-1] <= S) ){
						ns = s + V[i+1][j-1];
						cnt[i+1][j-1][ns] += cnt[i][j][s];
						np = path[ i ][ j ][ s ] << 1LL; // Left path
						if ( st[i+1][j-1][ns] > st[i][j][s] ){
							st[ i + 1 ][ j - 1 ][ ns ] = st[i][j][s];
							path[i+1][j-1][ns] = np;
						}
						else if ( st[i+1][j-1][ns] == st[i][j][s] && np < path[i+1][j-1][ns] ) {
							path[i+1][j-1][ns] = np;
						}
					}
				}
			}
		}
	}

	for ( int i=0; i < N-1; ++i ){
		for ( int j=0; j <= i; ++j ){
			for ( int s=0; s <= S; ++s ){
				if ( cnt[N - 1 + i][j][s] ){
					ns = s + V[N + i][j];
					if ( ns <= S ){  // Left path
						np = path[N - 1 + i][j][s] << 1LL;
						cnt[ N + i ][j][ns] += cnt[N - 1 + i][j][s];
						if ( st[N + i][j][ns] > st[N - 1 + i][j][s] ){
							st[ N + i ][j][ns] = st[N - 1 + i][j][s];
							path[N + i][j][ns] = np;
						}
						else if ( st[N + i][j][ns] == st[N - 1 + i][j][s] && np < path[N + i][j][ns] ){
							path[N+i][j][ns] = np;
						}
					}
					ns = s + V[N + i][j + 1];
					if ( ns <= S ){  // Right path
						np = (path[N - 1 + i][j][s] << 1LL) | 1LL;
						cnt[N + i][j + 1][ns] += cnt[N - 1 + i][j][s];
						if ( st[N+i][j+1][ns] > st[N-1+i][j][s] ){
							st[N + i][j + 1][ns] = st[N - 1 + i][j][s];	
							path[N+i][j+1][ns] = np;
						}
						else if ( st[N+i][j+1][ns] == st[N-1+i][j][s] && np < path[N+i][j+1][ns] ){
							path[N+i][j+1][ns] = np;
						}
					}
				}
			}
		}
	}

	long long res = 0;
	int beg = INT_MAX;
	long long bpath = LLONG_MAX;
	for ( int i=0; i < N; ++i ){
		res += cnt[2*N-2][i][S];
		if ( beg > st[2*N-2][i][S] ){
			beg = st[2*N-2][i][S];
			bpath = path[2*N-2][i][S];
		}
		else if (beg == st[2*N-2][i][S] && bpath > path[2*N-2][i][S] ) {
			bpath = path[2*N-2][i][S];
		}
	}

	printf("%lld\n", res);
	if ( res ){ 
		printf("%d ", beg);
		for ( int i=2*N - 3; i >= 0; i-- ){
			if ( (bpath >> i) & 1 ) putchar('R');
			else putchar('L');
		}
	}
	puts("");
}

int main(){
	while ( scanf("%d %d", &N, &S) && (N + S) )
		process();
	return 0;
}
