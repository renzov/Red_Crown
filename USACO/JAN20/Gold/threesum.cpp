#include<cstdio>
#include<cstdlib>
using namespace std;

const int OFFSET = 1000000;
const int MAXN = 5005;
long long res[MAXN][MAXN];
int frec[2*OFFSET + 5];
int A[MAXN];

int main(){
	freopen ("threesum.in", "r", stdin);
	freopen ("threesum.out", "w", stdout);	

	int N, Q;
	int sum;
	scanf("%d %d", &N, &Q);
	for ( int i=0; i < N; ++i )
		scanf("%d", A + i);
	
	//First we calculate cnt[i][k] = # of indices j s.t: i < j < k && A[i] + A[j] + A[k] == 0
	for ( int k=0; k < N; ++k ){
		for ( int i=k - 1; i >= 0; --i ){
			sum = OFFSET - A[i] - A[k];
			if ( sum >= 0 && sum <= 2*OFFSET )
				res[i][k] = frec[sum];

			frec[ A[i] + OFFSET ]++;	// for next iteration
		}
		// Undo the changes
		for ( int i=k - 1; i >= 0; --i )
			frec[ A[i] + OFFSET ]--;
	}

	// Now, calculate the answer for each subarray
	int j;
	for ( int len=3; len <= N; ++len ){
		for ( int i=0; i + len <= N; ++i ){
			j = i + len - 1;
			res[i][j] += (res[i][j - 1] + res[i + 1][j] - res[i + 1][j - 1]);
		}
	}
	int l, r; 
	while ( Q-- ){
		scanf("%d %d", &l, &r);
		l--, r--;
		printf("%lld\n", res[l][r]);
	}  
	return 0;
}
