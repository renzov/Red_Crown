#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 1024;
int d[MAXN];

void process(){
	int N;
	scanf("%d", &N);
	for ( int i=0; i < N; ++i )
		scanf("%d", d + i );
	sort(d, d + N);
	reverse( d, d + N );
	int sum = 0;
	int left;
	for ( int i=0; i < N; ++i ) sum += d[i];
	if ( sum & 1 ){
		puts("no");
		return;
	}
	// Erdos-Gallai criteria
	for ( int i=N; i >= 1; --i ){
		left = 0;
		for ( int j=i + 1; j <= N; ++j )
			left += min(i, d[j - 1]);

		if ( sum > i*(i - 1) + left ){
			puts("no");
			return;
		}

		sum -= d[i - 1];
	}
	puts("yes");
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}
