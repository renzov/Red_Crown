#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 1000005;
int X[MAXN];

int main(){

	int N;

	scanf("%d", &N);
	for ( int i=0; i < N; ++i )
		scanf("%d", X + i);
	sort( X, X + N );

	int l = X[1] - X[0];

	for ( int i=2; i < N && l > 1; ++i ){
		l = __gcd( l, X[i] - X[i - 1] );
	}
	long long res = 0;
	for ( int i=1; i < N; ++i ){
		res += ((X[i] - X[i - 1])/l - 1);
	}
	printf("%lld\n", res);
	return 0;
}
