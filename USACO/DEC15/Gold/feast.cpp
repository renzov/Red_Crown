#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXT = 5000002;
bool can[2][MAXT];
int res = -1;
int A, B, T;

void dfs( const int &t, const int &x ){
	res = max( x, res );
	can[t][x] = true;
	// drink water
	if ( !t && !can[1][x >> 1] )
		dfs( 1, x >> 1 );
	// eat A
	if ( x + A <= T && !can[t][x + A] )
		dfs( t, x + A );
	// eat B
	if ( x + B <= T && !can[t][x + B] )
		dfs( t, x + B );
}

int main(){
	freopen("feast.in", "r", stdin );
	freopen("feast.out", "w", stdout );
	scanf("%d %d %d", &T, &A, &B);
	dfs( 0, 0 );
	printf("%d\n", res );
	return 0;
}
