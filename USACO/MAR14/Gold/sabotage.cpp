#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int MAXN = 100005;
int A[MAXN];
double S[MAXN];
double mini[MAXN];
int N;

bool possible( const double &delta ){
	S[0] = 0.0;
	for ( int i=1; i <= N; ++i ){
		S[i] = S[i - 1] + A[i] - delta;
	}
	mini[1] = S[1];
	for ( int i=2; i < N; ++i )
		mini[i] = min( S[i], mini[i - 1] );

	for ( int i=2; i < N; ++i ){
		if ( (S[N] + mini[i - 1]) <= S[i] )
			return true;
	}
	return false;
}

int main(){
	freopen ("sabotage.in", "r", stdin);
	freopen ("sabotage.out", "w", stdout);
	
	scanf("%d", &N);
	for ( int i=1; i <= N; ++i )
		scanf("%d", A + i);
	
	double l = 0.0;
	double r = (double) *max_element( A + 1, A + (N + 1) ); 
	double m;
	
	for ( int k=0; k < 50; ++k ){
		m = ( l + r ) / 2;
		if ( possible(m) )
			r = m;
		else
			l = m;
	}
	printf("%.3f\n", r);
	return 0;
}
