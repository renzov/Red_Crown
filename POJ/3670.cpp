#include <cstdio>
#include <algorithm>
#include <climits>
using namespace std;

const int MAXN = 30005;
int V[MAXN];
int asc[MAXN][3];
int des[MAXN][3];

int main(){

	int N;
	int v;

	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){ 
		scanf("%d", V + i);
		V[i]--;
	}
	
	for ( int j=0; j < 3; ++j ){
		v = ( V[N-1] == j )? 0:1;
		asc[N-1][j] = v;
		des[N-1][j] = v;
	}
	
	for ( int i=N-2; i >= 0; --i ){
		for ( int j=0; j < 3; ++j ){
			v = ( V[i] == j )? 0:1;
			asc[i][j] = asc[i+1][j];
			des[i][j] = des[i+1][j];
			if ( j < 2 ) asc[i][j] = min( asc[i][j], asc[i+1][j+1] );
			if ( j < 1 ) asc[i][j] = min( asc[i][j], asc[i+1][j+2] );
			if ( j > 0 ) des[i][j] = min( des[i][j], des[i+1][j-1] );
			if ( j > 1 ) des[i][j] = min( des[i][j], des[i+1][j-2] );
			asc[i][j] += v;
			des[i][j] += v;
		}
	}
	int res = INT_MAX;
	for ( int j=0; j < 3; ++j ){
		res = min( res, min( asc[0][j], des[0][j] ) );
	}
	printf("%d\n", res);
	return 0;
}

