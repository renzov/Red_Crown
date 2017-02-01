#include<cstdio>
using namespace std;

int main(){
	int L, K, cnt, up;
	long long N, l, r, m, sum;
	while ( scanf("%d %d", &L, &K) != EOF ){
		N = (long long)L * L;	
		if ( K == 1 ){ printf("%lld\n", N); continue; }
		l = 1, r = N/K + 1;
		up = 2 * L - 1;
		while ( r - l > 1 ){
			m = ( l + r ) >> 1;
			cnt = 0;
			sum = 0;
			for ( int i=1; i <= up; i += 2 ){
				sum += i;
				if ( sum >= m ){
					sum = 0;
					cnt++;
					if ( cnt >= K ) break;
				}
			}
			if ( cnt >= K ) l = m;
			else r = m;
		}
		printf("%lld\n", l);
	}
	return 0;
}
