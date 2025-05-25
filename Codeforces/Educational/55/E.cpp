#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;
const int MAXN = 500005;

int A[MAXN];
int cnt[ MAXN ];
int best[ MAXN ];

// Idea: separate query into two parts, inclusion-exclusion

int main(){
	int N, C;
	int totalC = 0;

	scanf("%d %d", &N, &C);
	for ( int i = 1; i <= N; ++i ){
		scanf("%d", A + i );
		if ( C == A[i] ) totalC++;
	}

	fill( best, best + MAXN, INT_MAX );
	
	int res = totalC;
	int val;
	for ( int i = 1; i <= N; ++i ){
		cnt[ A[i] ]++;
		if ( A[i] == C ){ 
			totalC--;
			continue;
		}
		val = cnt[ A[i] ];
		best[ A[i] ] = min( best[ A[i] ], val - cnt[ C ] );
		res = max( res, val - best[ A[i] ] + 1 + totalC );
	}
	printf("%d\n", res );
	return 0;
}
