#include<cstdio>
using namespace std;
const int MAXN = 1024;
char S[MAXN];
int N, M;

bool test( const int &L ){
	int i;
	bool ok;

	for ( i = 0; (i + L) < N; i += L ){
		ok = true;
		for ( int j=0; j < L && ok; ++j )
			ok &= ( S[j] == S[i + j] );
		if ( !ok ) return false;
	}
	for ( int j=0; i < N && ok; ++j, i++ )
		ok &= ( S[j] == S[i] );
	return ok;
}

int main(){
	scanf("%d %d %s", &N, &M, S);
	// look for the prefix
	int L = 1;
	for ( ; L < N; ++L ){
		if ( test( L ) )
			break;
	}

	int p = N % L;
	for ( int i=0; i < M; ++i ){
		putchar(S[ p ]);
		p++;
		p %= L;
	}
	puts("");
	return 0;
}
