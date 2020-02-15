#include<cstdio>
#include<algorithm>
using namespace std;

int score[10];

void process(){
	int N;
	int p, s;

	fill(score, score + 8, 0);
	scanf("%d", &N);
	while ( N-- ){
		scanf("%d %d", &p, &s);
		p--;
		if ( p < 8 )
			score[p] = max( s, score[p] );
	}
	int res = 0;
	for ( int i=0; i < 8; ++i )
		res += score[i];
	printf("%d\n", res);
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}
