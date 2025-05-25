#include<cstdio>
using namespace std;
char B[16][16];
int sol[8];
bool ucol[8] = {0};
bool udiag1[16] = {0};
bool udiag2[16] = {0};
int res = 0;			// counts the number of solutions

inline void update(const int &r, const int &c){
	ucol[c] ^= true;
	udiag1[7 + r - c] ^= true;
	udiag2[r + c] ^= true;
}

void backtrack( const int &r ){
	if ( r >= 8 ){	// new solution found
		res++;
		return; 
	}
	// try every valid column
	for ( int c = 0; c < 8; ++c ){
		if ( ucol[c] || udiag1[7 + r - c] || udiag2[r + c] || B[r][c] == '*' )
			continue;
		// it is a valid placement
		sol[r] = c;
		update( r, c );
		backtrack( r + 1 );
		update( r, c );
	}
}

int main(){
	// read chessboard	
	for ( int i = 0; i < 8; ++i )
		scanf("%s", B + i );
	backtrack( 0 );
	printf("%d\n", res);
	return 0;
}
