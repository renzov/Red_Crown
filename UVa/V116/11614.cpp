#include<cstdio>

using namespace std;

const long long M = 1414213563LL;

int main(){
	int runs;
	long long n;

	scanf("%d",&runs);
	while (runs--){
		scanf("%lld",&n);	
		if (n == 0){ 
			puts("0");
			continue;
		}
		n <<= 1;
		long long l = 1;
		long long r = M;
		long long m;
		while ( r-l > 1 ){
			m = (l + r) >> 1;
			if ((m * (m + 1)) <= n)
				l = m;
			else 
				r = m;
		}
		printf("%lld\n",l);
	}
	return 0;
}
