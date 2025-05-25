#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 128;
const int LEN = 16;

char A[MAXN][LEN];
char B[MAXN][LEN];
int N;

int frec( char *S, const char &c ){
	int cnt = 0;
	for ( int i=0; S[i]; ++i )
		if ( S[i] == c ) cnt++;
	return cnt;
}

int main(){
	freopen("blocks.in", "r", stdin );
	freopen("blocks.out", "w", stdout );

	
	scanf("%d", &N);
	for ( int i=0; i < N; ++i )
		scanf("%s %s", A[i], B[i]);

	for ( int i=0; i < 26; ++i ){
		int sum = 0;
		for ( int j=0; j < N; ++j )
			sum += max( frec( A[j], (char)('a' + i) ), frec( B[j], (char)('a' + i) ) );
		printf("%d\n", sum);
	}
	return 0;
}
