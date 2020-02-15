#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;
const int MAXN = 100005;

char S[MAXN];
int last[32];

void process(){
	int N;
	int idx;
	int mini = INT_MAX;
	scanf("%d %s", &N, S);
	fill( last, last + 26, -1 );
	for ( int i=0; i < N; ++i ){
		idx = S[i] - 'a';
		if ( last[idx] >= 0 ) mini = min( mini, i - last[idx] );
		last[idx] = i;
	}
	if ( mini == INT_MAX ) puts("0");
	else printf("%d\n", N - mini);
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}
