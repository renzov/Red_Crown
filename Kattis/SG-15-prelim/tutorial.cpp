#include<cstdio>
#include<cmath>
using namespace std;
const double EPS = 1e-6;

int main(){
	long long N, M;
	int T;
	long long tmp;
	bool ok;
	double v;
	scanf("%lld %lld %d", &M, &N, &T);

	switch (T) {
		case 1: tmp = 1;
				for ( int i=N; i > 0 && tmp <= M; --i )
						tmp *= i;
				ok = tmp <= M;
				break;
		case 2:	tmp = 1;
				for ( long long i=0; tmp <= M && i < N; ++i )
					tmp <<= 1;
				ok = tmp <= M;
				break;
		case 3:	tmp = 1;
				for ( int i=0; i < 4 && tmp <= M; ++i )
					tmp *= N;
				ok = tmp <= M;
				break;
		case 4: tmp = 1;
				for ( int i=0; i < 3 && tmp <= M; ++i )
					tmp *= N;
				ok = tmp <= M;
				break;
		case 5:	tmp = 1;
				for ( int i=0; i < 2 && tmp <= M; ++i )
					tmp *= N;
				ok = tmp <= M;
				break;
		case 6: v = N * log2( (double)N );
				ok = fabs( M - v ) < EPS || v < M;  
				break;
		case 7:	ok = N <= M;
				break;
	}
	puts(ok? "AC":"TLE");
	return 0;
}
