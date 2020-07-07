#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;

const int MAXN = 100005;
const int DIM = 7;

int P[MAXN][DIM];

int main(){
	int N, D;

	scanf("%d %d", &N, &D);
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < D; ++j )
			scanf("%d", P[i] + j);
	
	int res = 0;
	int mini, maxi; 
	int x;
	for ( int k = 0; k < (1 << (D - 1)); ++k ){
		mini = INT_MAX;
		maxi = INT_MIN;
		for ( int i=0; i < N; ++i ){
			x = 0;
			for ( int j=0; j < D; ++j ){
				if ( (k >> j)&1 )
					x -= P[i][j];
				else
					x += P[i][j];
			}
			mini = min( mini, x );
			maxi = max( maxi, x );
		}
		res = max( res , maxi - mini );
	}
	printf("%d\n", res);
	return 0;
}
