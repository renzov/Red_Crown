#include<cstdio>
#include<algorithm>
#include<climits>
using namespace std;

const int MAXN = 64;
int f[MAXN];

int main(){
	int N, M;

	scanf("%d %d", &N, &M);
	for ( int i=0; i < M; ++i ) scanf("%d", f + i);
	sort(f, f + M);
	
	int res = INT_MAX;
	for ( int i=0; i + N <= M; ++i ){
		res = min( res, f[i+N-1] - f[i] );
	}
	printf("%d\n", res);
	return 0;
}
