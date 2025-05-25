#include<cstdio>
using namespace std;

const int MAXN = 305;

int d[MAXN][MAXN];

int main(){

	int N;

	scanf("%d", &N);

	for ( int i = 0; i < N; ++i )
		for ( int j = 0; j < N; ++j )
			scanf("%d", d[i] + j);

	bool ok = true;

	for ( int i = 0; i < N && ok; ++i )
		for ( int j = 0; j < N && ok; ++j ){
			if ( i != j )
				for ( int k = 0; k < N; ++k )
					ok &= ( d[i][j] <= ( d[i][k] + d[k][j] ) );

		}

	if ( ok ){
		for ( int i = 0; i < N; ++i ){
			printf("%d", d[i][0]);
			for ( int j = 1; j < N; ++j )
				printf(" %d", d[i][j]);
			puts("");
		}
	}
	else {
		puts("-1");
	}
	return 0;
}
