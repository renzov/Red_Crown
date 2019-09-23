#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXR = 9;
const int MAXC = 9;
const int INF = 9999999;

char T[MAXR][MAXC];
int memo[MAXR][MAXC][1 << MAXC][1 << 3][2];

int solve( int r, int c, int mC, int mB, bool odd ){
	if ( r >= MAXR ) return mC == 0? 0:INF;		// Check if every column has even parity
	if ( c >= MAXC ){	// Finish one row
		if ( odd ) return INF;	// Check if row has even parity
		if ( ((r % 3) == 2) && mB ) return INF;	// When we finish a block of 3 rows, check paritty of blocks
		return solve( r + 1, 0, mC, mB, false );
	}
	if ( memo[r][c][mC][mB][odd] != -1 ) return memo[r][c][mC][mB][odd];
	int &res = memo[r][c][mC][mB][odd];
	// Now we have two options, set to 1 or set to 0
	// First, we set to 1, we have to change the parity at column c and block (c/3) of the corres. masks.
	res = !T[r][c] + solve( r, c + 1, mC ^ (1 << c), mB ^ (1 << (c/3)), !odd );
	// Now, we set to 0, parities are maintained
	res = min( res, T[r][c] + solve( r, c + 1, mC, mB, odd ) );
	return res;
}

int main(){

	for ( int i=0; i < MAXR; ++i )
		scanf("%s", T[i]);
	for ( int i=0; i < MAXR; ++i )
		for ( int j = 0; j < MAXC; ++j )
			T[i][j] -= '0';
	memset( memo, -1, sizeof(memo) );
	printf("%d\n", solve( 0, 0, 0, 0, false ));
	return 0;
}
