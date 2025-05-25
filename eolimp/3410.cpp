#include<cstdio>
#include<algorithm>

using namespace std;
const int MAXN = 55;
const int MAXSET = 25;

long long G[MAXN];
int clique[1 << MAXSET];	// clique[ S ] = size of max clique spanned by S

void process( const int &N ){
	int n = N >> 1;
	int m = N - n;
	int sub, v; 
	long long NG;
	int res = 1;

	clique[ 0 ] = 0;
	for ( int mask = 1; mask < ( 1 << m ); ++mask ){
		for ( v = 0; v < m; ++v )
			if ( (mask >> v) & 1 ){
				sub = mask ^ ( 1 << v );
				clique[mask] = max( clique[sub], 1 + clique[ (G[n + v] >> n) & sub ] );
				res = max( res, clique[mask] );
				break;
			}
	}
	
	for ( int mask = 1; mask < ( 1 << n ); ++mask ){
		NG = (1 << N) - 1;
		for ( int i=0; i < n; ++i )
			if ( (mask >> i) & 1 ){
				NG &= G[i];
			}
		if ( (NG & mask) == mask ){	// clique
			res = max( res, __builtin_popcount(mask) + clique[ NG >> n ] );	
		}
	}
	printf("%d\n", res);
} 

int main(){
	int N;
	char b;
	
	while ( scanf("%d", &N) && N ){
		// Read the graph
		for ( int i = 0; i < N; ++i ){
			G[i] = 1LL << i;
			for ( int j = 0; j < N; ++j ){
				scanf(" %c", &b);
				if ( b == '1' )
					G[i] |= ( 1LL << j );
			}
		}
		if ( N == 1 ) puts("1");
		else process( N );
	}
	return 0;
}
