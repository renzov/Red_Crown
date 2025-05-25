#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define X first
#define Y second
using namespace std;
typedef pair<long long, long double> point;
const int MAXN = 200005;

point P[MAXN];

int main(){

	int N;

	scanf("%d", &N);
	for ( int i=0; i < N; ++i )
		scanf("%lld %Lf", &P[i].X, &P[i].Y);
	
	sort( P, P + N );

	long double bestN = 0;
	long long bestD = 1;

	for ( int i=1; i < N; ++i ){
		long double num = fabs( P[i].Y - P[i - 1].Y );
		long long den = P[i].X - P[i - 1].X;
		// Test if we have a better gradient
		if ( bestN * den < bestD * num ){
			bestN = num, bestD = den;
		}
	}
	
	printf("%.6Lf\n", bestN / bestD );
	return 0;
}
