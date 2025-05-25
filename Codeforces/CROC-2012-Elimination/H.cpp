#include<cstdio>
#include<cstring>
using namespace std;

const int MAXN = 5005;
char S[MAXN];
int N;

int palin[MAXN][MAXN];
int cntpalin[MAXN][MAXN];

void precalc(){
	// Base case
	for ( int i = 0; i < N; ++i ){
		palin[i][i] = 1;
		cntpalin[i][i] = 1;
	}
	for ( int i = 1; i < N; ++i ){
		palin[i - 1][i] = ( S[i - 1] == S[i] )? 1:0;
		cntpalin[i - 1][i] = 2 + palin[i - 1][i];
	}
	// DP - recurrence relation
	int j;
	for ( int len = 3; len <= N; ++len ){
		for ( int i = 0; i + len - 1 < N; ++i ){
			j = i + len - 1;
			palin[i][j] = ( palin[i + 1][j - 1] && ( S[i] == S[j] ) )? 1:0;
			cntpalin[i][j] = cntpalin[i][j - 1] + cntpalin[i + 1][j] - cntpalin[i + 1][j - 1] + palin[i][j];
		}
	}
}

int main(){

	scanf("%s", S);
	N = strlen(S);
	precalc();
	// Process queries
	int Q, l, r;
	scanf("%d", &Q);
	while ( Q-- ){
		scanf("%d %d", &l, &r);
		l--, r--;
		printf("%d\n", cntpalin[l][r]);
	}
	return 0;
}
