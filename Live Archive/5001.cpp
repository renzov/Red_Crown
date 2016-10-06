#include<cstdio>
using namespace std;

const int MAXN = 65;

long long res[MAXN];

int main(){
	int N;
	int cases = 0;
	res[1] = res[2] = res[3] = 1;
	for ( int i=4; i < MAXN; ++i )
		res[i] = res[i-1] + res[i-2] + res[i-3];
	while ( scanf("%d", &N) && N ){
		cases++;
		printf("Case %d: %lld\n", cases, res[N]);
	}
	return 0;
}
