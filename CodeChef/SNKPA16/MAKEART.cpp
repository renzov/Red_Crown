#include<cstdio>
using namespace std;
const int MAXN = 100005;
int S[MAXN];
void process(){
	int N;

	scanf("%d", &N);
	int last = -1;
	int cnt = 0;
	int c;
	int M = 0;
	for ( int i=0; i < N; ++i ){
		scanf("%d", &c);
		if ( c != last ){
			S[M++] = cnt;
			last = c;
			cnt = 1;
		}
		else {
			cnt++;
		}
	}
	S[M] = cnt;
	bool ok = false;
	for ( int i=1; i <= M && !ok; ++i )
		ok = S[i] >= 3;

	puts( ok? "Yes":"No" );
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- ) process();
	return 0;
}
