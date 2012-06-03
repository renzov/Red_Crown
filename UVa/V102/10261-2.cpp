#include<cstdio>
int ar[201][10001];
int len;

void pr( int i, int j ) {
	if( i == 0 ) return;
	pr( i-1, ar[i][j] );
	printf( (j == ar[i][j]) ? "port\n" : "starboard\n" );
}

int main() {
	int runs;
	int i, j, k, x, y, z, n;
	scanf("%d",&runs);
	while (runs--){
		scanf( "%d", &len );
		len *= 100;
		for( i = 0; i <= 200; i++ ) for( j = 0; j <= 10000; j++ ) ar[i][j] = -1;
		ar[0][0] = 0;
		y = 0;
		for( i = 0; i < 200; i++ ) {
			 scanf( " %d", &x );
			 if( !x ) break;
			 y += x;
			 z = 0;
			 for( j = 0; j <= 10000; j++ ) if( ar[i][j] >= 0 ) {
				if( j+x <= len && y-x-j <= len ) {ar[i+1][j+x] = j; z = 1;}
				if( j <= len && y-j <= len ) {ar[i+1][j] = j; z = 1;}
			 }
			 if( !z ) break;
		}
		printf( "%d\n", i );
		for( j = 0; j <= 10000; j++ ) if( ar[i][j] >= 0 ) break;
		pr( i, j );
		if (runs) puts("");
	}

	return 0;
}