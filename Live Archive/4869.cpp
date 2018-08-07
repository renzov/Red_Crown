#include<cstdio>
#include<algorithm>

using namespace std;

// dp[i] = maximum sum of a nonempty subinterval ending at i
// dp[i] = max( A[i], dp[i-1] + A[i] )

int main(){
	int N;
	int res;  // overall best
	int best; // dp[i]
	int val;  // A[i]
	int last; // dp[i-1]
	
	while ( scanf("%d", &N) && N ){
		res = -500000000;
		last = -500000000;
		for ( int i=0; i < N; ++i ){
			scanf("%d", &val);
			best = max( val , last + val );
			res = max( best, res );
			last = best;
		}
		printf("%d\n", res);
	}
	return 0;
}
