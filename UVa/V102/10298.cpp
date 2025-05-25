#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN = 1000005;

char S[MAXN];
int p[MAXN];
int N;

void prefix_function(){
	p[0] = 0;
	for ( int i = 1; i < N; ++i ){
		int j = p[i - 1];
		while ( j > 0 && S[j] != S[i] )
			j = p[j - 1];
		if ( S[i] == S[j] )
			j++;
		p[i] = j;
	}
}

void process(){
	N = strlen( S );
	prefix_function();
	int K = N - p[N - 1];
	int ans;

	if ( N % K ){
		ans = 1;
	}
	else {
		ans = N / K;
	}
	printf("%d\n", ans);
}

int main(){
	while ( scanf("%s", S) && S[0] != '.' )
		process();
	return 0;
}
