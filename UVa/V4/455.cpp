#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN = 1024;

int p[MAXN];
char S[MAXN];
int N;

void prefix_function(){
	p[0] = 0;
	for ( int i = 1; i < N; ++i ){
		int j = p[ i - 1 ];
		while ( j > 0 && S[i] != S[j] )
			j = p[j - 1];
		if ( S[j] == S[i] )
			j++;
		p[i] = j;
	}
}

int main(){
	int runs, K;
	scanf("%d", &runs);

	while ( runs-- ){
		scanf("%s", S);
		N = strlen( S );
		prefix_function();
		K = N - p[N - 1];
		if ( N % K ) printf("%d\n", N);
		else printf("%d\n", K);
		if ( runs ) puts("");
	}
	return 0;
}
