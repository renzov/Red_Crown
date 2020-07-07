#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 300005;
int N, K;

int A[MAXN];
double S[MAXN];
double mini[MAXN];

bool isPossible( const double &X ){
	S[0] = 0.0;
	mini[0] = 0;	
	for ( int i=1; i <= N; ++i ){
		S[i] = S[i - 1] + A[i] - X;
		mini[i] = min( mini[i - 1], S[i] );
	}
	for ( int i=1; i <= N; ++i ){
		if ( i - K >= 0 && S[i] >= mini[i - K] ){
			return true;
		}
	}
	return false;
}

int main(){
	int maxVal = 0;
	scanf("%d %d", &N, &K);
	for ( int i=1; i <= N; ++i ){
		scanf("%d", A + i);
		maxVal = max( A[i], maxVal );	
	}
	if ( isPossible( (double) maxVal ) ){
		printf("%.5f\n", (double)maxVal);
	}
	else {
		double l = 1;
		double r = maxVal;	
		double m;
		for ( int i=0; i < 50; ++i ){
			m = ( l + r ) / 2;
			if ( isPossible(m) )
				l = m;
			else 
				r = m;
		}
		printf("%.5f\n", l);
	}
	return 0;
}
