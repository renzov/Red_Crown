#include<cstdio>
using namespace std;

int process(){
	int N, x;
	int odd = 0, even = 0;
	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d", &x);
		if ( x & 1 ) odd++;
		else even++;
	}
	if ( odd == N || even == N ) puts("YES");
	else puts("NO");
}

int main(){
	int runs;

	scanf("%d", &runs);
	while ( runs-- ) process();
	return 0;
}
