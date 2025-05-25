#include<cstdio>
using namespace std;

long long odds( const long long &x ){
	// returns odd numbers from 1 to x
	return (x + 1) >> 1;
} 

int main(){
	long long N;
	int runs;

	scanf("%d\n", &runs);
	while ( runs-- ){
		scanf("%lld", &N);
		long long A = N - (N >> 1); // numbers x s.t 2*x > N
		long long bound = (N - 1) / 3; // max. x s.t. 3*x + 1 <= N
		long long B = odds( N ) - odds( bound );
		printf("%lld\n", A + B );
	}
	return 0;
}
