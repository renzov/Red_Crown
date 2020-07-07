#include<cstdio>
#include<algorithm>
#include<cstdlib>
using namespace std;
const int MAXN = 1 << 11;

int N, X, Y;
int res[MAXN];

int main(){
	int d;
	scanf("%d %d %d", &N, &X, &Y);
	X--, Y--;

	for ( int i=0; i < N; ++i )
		for ( int j=i + 1; j < N; ++j ){
			d = min( abs(i - X) + abs(j - Y) + 1, abs(i - Y) + abs(j - X) + 1 );
			d = min( d, j - i );
			res[d]++;
		}
	for ( int i=1; i < N; ++i )
		printf("%d\n", res[i]);
	return 0;
}
