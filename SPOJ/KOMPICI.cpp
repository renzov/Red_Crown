#include<cstdio>
using namespace std;
const int MAXN = 500005;

long long cnt[MAXN];
char S[32];

int main(){
	
	int N;
	int mask;

	scanf("%d\n", &N);
	for ( int i=0; i < N; ++i ){
		mask = 0;
		scanf("%s", S);
		for ( int j=0; S[j]; ++j ){
			mask |= ( 1 << (S[j] - '0') );
		}
		cnt[mask]++;
	}
	// To perform the count, first consider the pairs (x, y)
	// where x and y have the same mask. After that count the pairs that 
	// have different mask but at least one element in common
	long long res = 0;
	for ( int i=0; i < (1 << 10); ++i ){
		if ( cnt[i] ) res += (( cnt[i] * ( cnt[i] - 1 ) ) >> 1);
		for ( int j=i + 1; j < (1 << 10); ++j )
			if ( i & j ) res += (cnt[i] * cnt[j]);
	}
	printf("%lld\n", res);
	return 0;
}
