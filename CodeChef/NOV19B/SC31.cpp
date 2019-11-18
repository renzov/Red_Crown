#include<cstdio>
using namespace std;

void process(){
	int res = 0;
	int x;
	char s[32];
	int N;

	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%s", s);
		x = 0;
		for ( int j=0; s[j]; ++j )
			if ( s[j] == '1' )
				x |= ( 1 << j );
		res ^= x;
	}
	printf("%d\n", __builtin_popcount(res));
}
	
int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}
