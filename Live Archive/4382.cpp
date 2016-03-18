#include <cstdio>
const int MAXN = 3*1000000 + 8; 
int S[1000005] = {0};
bool np[MAXN] = {0};

void sieve(){
	// 1733^2 > 3*10^6 + 7
	for ( int i=3;  i < 1733; ++i ){
		if ( !np[i] ){
			for ( int j=i*i; j < MAXN; j += (i << 1) )
				np[j] = true;
		}
	}
}

int main(){
	sieve();
	S[0] = 0;
	// 3*i + 7 is odd <=> i is even
	for ( int i=2; i <= 1000000; i+=2 ){
		if ( !np[3*i + 7] ) S[i] = 1;
		S[i] += S[i-2];
	}
	for ( int i=1; i < 1000000; i+= 2 ) S[i] = S[i-1];

	int runs, n;

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &n);
		printf("%d\n", S[n]);
	}
	return 0;
}

