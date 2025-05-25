#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef pair<int,int> pii;
const int MAXN = 100005;

int ord[MAXN];
pii A[MAXN];
int best[MAXN];		// best[i] = index of the element on top of the stack of i elements
int bestV[MAXN];	// value of second coord. of the corresponding best[i]
int P[MAXN];		// P[i] = index of the previous element

bool cmp( const int &i, const int &j ){
	return A[i] < A[j];
}

int main(){
	freopen("people.in", "r", stdin);
	freopen("people.out", "w", stdout);

	int N;
	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d %d", &A[i].first, &A[i].second );
		A[i].second *= -1;	// we want to order increasing in first and decreasing in second
		ord[i] = i;
	}
	sort( ord, ord + N, cmp );
	
	best[0] = ord[0];
	bestV[0] = -A[ ord[0] ].second;
	P[ ord[0] ] = -1;
	int M = 1;	

	int idx, pos;

	for ( int i=1; i < N; ++i ){
		idx = ord[i];
		pos = lower_bound( bestV, bestV + M, -A[ idx ].second ) - bestV;
		if ( pos == M ){
			best[ M ] = idx;
			bestV[ M ] = -A[ idx ].second;
			P[ idx ] = best[ M - 1 ];
			M++;
		}
		else {
			
			if ( pos == 0 ) P[ idx ] = -1;
			else P[ idx ] = best[ pos - 1 ];

			if ( bestV[pos] > -A[idx].second ){
				bestV[pos] = -A[idx].second;
				best[pos] = idx;
			}
		}
	}
	printf("%d\n", M);
	idx = best[M - 1];
	printf("%d", idx + 1);
	while ( P[idx] != -1 ){
		idx = P[idx];
		printf(" %d", idx + 1);
	}
	puts("");
	return 0;
}
