#include<cstdio>
#include<algorithm>
using namespace std;
int T;
long long tprimes[1000005];
bool noprime[1000005] = {0};

void preprocess(){
	tprimes[0] = 4;
	T = 1;
	
	for ( long long i=3; i < 1000000; i += 2 )
		if ( !noprime[i] ){
			tprimes[T++] = i*i;
			for ( long long j=i*i; j < 1000000; j += (i << 1) )
				noprime[j] = true;
			
		}
}

int main(){
	
	preprocess();
	int N;
	long long x;
	scanf("%d", &N);
	while ( N-- ){
		scanf("%I64d", &x);
		if (binary_search( tprimes, tprimes + T, x ))
			puts("YES");
		else 
			puts("NO");
	}
	return 0;
}
