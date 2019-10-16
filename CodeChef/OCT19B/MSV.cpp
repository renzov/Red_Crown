#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 100005;
int cnt[ 10*MAXN ];
int A[MAXN];
int last[ 10*MAXN ]; 

void process(){
	int N;
	scanf("%d", &N);
	for ( int i=1; i <= N; ++i ){
		scanf("%d", A + i);
		last[ A[i] ] = i;
	}
	int Mx = 0;
	int x, res;
	int best = 0;
	for ( int i=1; i <= N; ++i ){	
		x = A[i];
		Mx = max( Mx, x );
		if ( last[x] != i ){ 	// It is suboptimal to find the value for the same number
			cnt[ x ]++;			// with lower index in the array <---
			continue;
		}
		res = 0;
		for ( int j=x; j <= Mx; j += x )
			res += cnt[j];
		if ( res > best ) best = res;
		cnt[ x ]++;
	}
	printf("%d\n", best);
    for ( int i=1; i <= N; ++i ) cnt[ A[i] ] = 0, last[ A[i] ] = 0;
}

int main(){

	int runs;
	scanf("%d", &runs);
	while ( runs-- ){ 
		process();	
	}
	return 0;
}

