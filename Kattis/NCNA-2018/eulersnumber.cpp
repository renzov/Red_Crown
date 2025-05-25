#include<cstdio>
#include<algorithm>
using namespace std;
const long double EPS = 1e-12;
const int MAXN = 32;
long double res[MAXN];

int main(){
	// precalc
	res[0] = 1;
	res[1] = 2;
	long long fact = 1LL;
	for ( int i = 2; i < 20; ++i ){
		fact *= i;
		res[i] = res[i - 1] + 1.0L/fact;
	}
	// Process input
	int N;
	scanf("%d", &N);
	N = min(N , 19);
	printf("%.15Lf\n", res[N]);
	return 0;
}
