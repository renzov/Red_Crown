#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 100005;

int f[MAXN];

void process(){
	int N;
	int a;
	scanf("%d", &N);
	for ( int i = 0; i < N; ++i ){
		scanf("%d", &a);
		a--;
		f[a] = i;
	}
	int b = 0;
	int e;
	int M = -1;
	bool first = true;
	for ( int i = 0; i < N; ){
		do {
			scanf("%d", &a);
			a--;
			M = max( f[a], M );
		}
		while ( M > i++ );
		if ( !first ) putchar(' ');
		first = false;
		printf("%d-%d", b + 1, i);
		b = i;
		M = -1;
	}
	puts("");
}

int main(){
	int runs;

	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}
