#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 128;
int T[MAXN];

int main(){
	int N, S;

	scanf("%d %d", &N, &S);
	for ( int i=0; i < N; ++i )
		scanf("%d", T + i );
	int M = *max_element( T, T + N );
	M *= S;
	printf("%d\n", (M + 999)/1000);
	return 0;
}
