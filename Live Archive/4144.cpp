#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN = 1024;

int minchange[MAXN][MAXN];
char S[MAXN];

void process(){
	int K;
	scanf("%s %d", S, &K);
	int N = strlen(S);
	int j;
	int res = 1;

	for ( int i=0; i < N; ++i )
		for ( int j=0; j < i; ++j )
			minchange[i][j] = 0;

	for ( int i=0; i < N; ++i ){ 
		minchange[i][i] = 0;
	}
	
	for ( int len=2; len <= N; ++len ){
		for ( int i=0; i + len <= N; ++i ){
			j = i + len - 1;
			minchange[i][j] = minchange[i + 1][j - 1] + ( S[i] != S[j] );
			if ( minchange[i][j] <= K ) 
				res = max( res, len );
		}
	}
	printf("%d\n", res);
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}
