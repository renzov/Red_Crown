#include<cstdio>
#include<cstring>
using namespace std;

const int MAXN = 100005;
char S[MAXN];
char P[MAXN];

int main(){
	
	int N, X, M;

	scanf("%d %d %s %d %s", &N, &X, S, &M, P);
	X--;
	putchar(S[X]);
	for ( int i = 0; i < M; ++i ){
		if ( P[i] == 'L' ) X--;
		else X++;
		putchar( S[X] );
	}
	puts("");
	return 0;
}
