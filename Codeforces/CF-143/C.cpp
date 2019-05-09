#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 100005;
int A[MAXN];

int main(){
	int N, K;
	scanf("%d %d", &N, &K);
	
	for ( int i=0; i < N; ++i )
		scanf("%d", A + i);
	sort( A, A + N );
	
	int left = K;
	int l = 0;
	int res = 0;
	int best;
	// Test every value as the answer
	for ( int i=0; i < N; ++i ){
		// check to move the pointer to the right
		while ( l < i && left < (long long)(A[i] - A[i-1])*(i - l) ){ //ERROR WAS OVERFLOW !!!!!
			left += (A[i - 1] - A[l]);
			l++;
		}
		if ( l < i ) left -= ( A[i] - A[i - 1] )*(i - l);
		//printf("After iteration %d: left %d - l = %d\n", i, left, l);
		if ( res < ( i - l + 1 ) ){
			res = i - l + 1;
			best = A[i];
		}

	}
	printf("%d %d\n", res, best);
	return 0;
}
