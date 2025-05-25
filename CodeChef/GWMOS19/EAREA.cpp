#include<cstdio>
using namespace std;
const int MAXN = 100005;

long long X[MAXN];
long long Y[MAXN];

int main(){
	int N;

	scanf("%d", &N);
	
	for ( int i=0; i < N; ++i )
		scanf("%lld %lld", X + i, Y + i);
	
	X[N] = X[0], Y[N] = Y[0];
	X[N + 1] = X[1], Y[N + 1] = Y[1];

	// Use the linearity of expectation and the fact that 
	// random variables are independent to show: res = 2 * area( P ) / 8

	long long sum = 0LL;
	for ( int i=0; i < N; ++i ){
		sum += (X[i] + X[i  + 1]) * (Y[i + 1] + Y[i + 2]);
		sum -= (X[i + 1] + X[i + 2]) * (Y[i] + Y[i + 1]);
	}
	
	printf("%.7f\n", (double)sum / 8.0 );
	return 0;
}
