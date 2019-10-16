#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 100005;
int cnt[ 10*MAXN ];
int A[MAXN];

void process(){
	int N;
	scanf("%d", &N);
	for ( int i=0; i < N; ++i ) scanf("%d", A + i);
	int Mx = 0;
	int x, res;
	int best = 0;
	for ( int i=0; i < N; ++i ){
		x = A[i];
		res = 0;
		for ( int j=x; j <= Mx; j += x )
			res += cnt[j];
		if ( res > best ) best = res;
		cnt[ x ]++;
		Mx = max( Mx, A[i] );
	}
	printf("%d\n", best);
    for ( int i=0; i < N; ++i ) cnt[ A[i] ] = 0;
}

int main(){

	int runs;
	scanf("%d", &runs);
	while ( runs-- ){ 
		process();	
	}
	return 0;
}

