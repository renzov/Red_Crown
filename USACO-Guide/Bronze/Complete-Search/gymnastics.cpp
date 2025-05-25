#include<cstdio>
using namespace std;
const int MAXN = 32;
int P[MAXN][MAXN];

int N, K;
bool better( const int &i, const int &j ){
	// Returns true iff P[i] < P[j]
	for ( int k=0; k < K; ++k )
		if ( P[i][k] >= P[j][k] ) return false;
	return true;
}

int main(){
	int x;

	freopen("gymnastics.in", "r", stdin);
	freopen("gymnastics.out", "w", stdout);

	scanf("%d %d", &K, &N);

	for ( int j=0; j < K; ++j )
		for ( int i=0; i < N; ++i ){
			scanf("%d", &x);
			x--;
			P[x][j] = i;
		}

	int res = 0;

	for ( int i=0; i < N; ++i )
		for ( int j=i + 1; j < N; ++j ){
			if ( better(i, j) || better(j, i) )
				res++;
		}
	
	printf("%d\n", res);
	return 0;
}
