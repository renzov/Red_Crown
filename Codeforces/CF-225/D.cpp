#include<cstdio>
using namespace std;

const int MAXN = 1024;
const int MAXV = 10005;
const int MOD = 1000000007;

int UB = 0;
int LB;

int A[MAXN];
int dp[2][2 * MAXV];
int suff[2][2 * MAXV];
int *act;
int *prev;
int *psuff;
int *asuff;

inline int getSuff( const int &x ){
	return ( x >= LB && x <= UB )? asuff[x]:0;
}

void printSuff(){
	puts("------------");
	for ( int i = LB; i <= UB; ++i )
		printf("suff[%d] = %d\n", i, asuff[i]);
	puts("------------");
}

int main(){
	int N;

	scanf("%d", &N);
	for ( int i = 0; i < N; ++i ){
		scanf("%d", A + i );
		UB += A[i];
	}
	LB = -UB;
	act = (dp[1] + UB);
	prev = (dp[0] + UB);
	asuff = (suff[0] + UB);
	psuff = (suff[1] + UB);
	//asuff[0] = 1;
	int *aux;	// for exchange pointers
	for ( int i = 0; i < N; ++i ){
		// update the suffix info
		for ( int j = LB; j <= UB; ++j ){
			if ( j == A[i] || j == -A[i] )  
				psuff[j] = ( getSuff( j - A[i] ) + getSuff( j + A[i] ) + 1 ) % MOD;
			else 
				psuff[j] = ( getSuff( j - A[i] ) + getSuff( j + A[i] ) ) % MOD;
		}
		// change pointers of suffixes
		aux = psuff;
		psuff = asuff;
		asuff = aux;
		//printSuff();		
		// calculate row of dp
		for ( int j = LB; j <= UB; ++j )
			act[j] = ( prev[j] + getSuff(j) ) % MOD;
		// change pointers to dp table
		aux = act;
		act = prev;
		prev = aux;
	}
	printf("%d\n", prev[0]);
	return 0;
}
