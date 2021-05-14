#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAXN = 128;

char A[MAXN];
char B[MAXN];
int len[MAXN][MAXN];
long long cnt[MAXN][MAXN];

void process(){
	fgets(A, MAXN, stdin); 
	fgets(B, MAXN, stdin);
	int N = strlen(A) - 1; 	// Remove the "\n" character
	int M = strlen(B) - 1;
	
	// Initialization
	for ( int i=0; i <= N; ++i ){
		len[i][0] = i;
		cnt[i][0] = 1;
	}
	for ( int j=0; j <= M; ++j ){
		len[0][j] = j;
		cnt[0][j] = 1;
	}

	for ( int i=1; i <= N; ++i )
		for ( int j=1; j <= M; ++j ){
			cnt[i][j] = 0;
			if ( A[i - 1] == B[j - 1] ){
				len[i][j] = len[i - 1][j - 1] + 1;
				cnt[i][j] = cnt[i - 1][j - 1];
			}
			else {
				len[i][j] = min( len[i][j - 1], len[i - 1][j] ) + 1;
				if ( (len[i][j - 1] + 1) == len[i][j] ){
					cnt[i][j] += cnt[i][j - 1];
				}
				if ( (len[i - 1][j] + 1) == len[i][j] ){
					cnt[i][j] += cnt[i - 1][j];
				}
			}
		}
	printf("%d %lld\n", len[N][M], cnt[N][M]);
}

int main(){
	int runs;

	scanf("%d", &runs); getchar();
	for ( int i=1; i <= runs; ++i ){
		printf("Case #%d: ", i );
		process();
	}
	return 0;
}
