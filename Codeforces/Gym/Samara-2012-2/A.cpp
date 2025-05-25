#include<cstdio>
using namespace std;

const int MAXN = 2505;

char M[MAXN][MAXN];

int U[MAXN][MAXN];
int L[MAXN][MAXN];
int D[MAXN][MAXN];
int R[MAXN][MAXN];

void preprocess( const int &n, const int &m ){
	// first row is already initialized to 0
	for ( int i = 1; i < n; ++i )
		for ( int j = 0; j < m; ++j )
			U[i][j] = ( M[i - 1][j] == '#' )? 0:( U[i - 1][j] + 1 );
	// last row is already initialize to 0
	for ( int i = n - 2; i >= 0; --i )
		for ( int j = 0; j < m; ++j )
			D[i][j] = ( M[i + 1][j] == '#' )? 0:( D[i + 1][j] + 1 );
	// first column is already initialized to 0
	for ( int j = 1; j < m; ++j )
		for ( int i = 0; i < n; ++i )
			L[i][j] = ( M[i][j - 1] == '#' )? 0:( L[i][j - 1]  + 1 );
	// last column is already initialized to 0
	for ( int j = m - 2; j >= 0; --j )
		for ( int i = 0; i < n; ++i )
			R[i][j] = ( M[i][j + 1] == '#' )? 0:( R[i][j + 1]  + 1 );

}

bool horizontal( const int &x1, const int &y1, const int &x2, const int &y2 ){
	// precondition: x1 == x2
	if ( y1 > y2 ) return horizontal( x2, y2, x1, y1 );
	// y1 <= y2
	return (y2 - y1) <= R[x1][y1];
}

bool vertical( const int &x1, const int &y1, const int &x2, const int &y2 ){
	// precondition y1 == y2
	if ( x1 > x2 ) return vertical( x2, y2, x1, y1 );
	// x1 <= x2
	return (x2 - x1) <= D[x1][y1];
}

int main(){

	int n, m, Q;
	int r1, c1, r2, c2;
	bool ok;

	scanf("%d %d", &n, &m);
	for ( int i = 0; i < n; ++i )
		scanf("%s", M + i );
	
	preprocess( n, m );
	// process the Q queries
	scanf("%d", &Q);
	while ( Q-- ){
		scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
		r1--, r2--, c1--, c2--;
		ok = false;
		if ( r1 != r2 && c1 != c2 ){
			// first we test point (r1, c2)
			if ( M[r1][c2] != '#' && horizontal( r1, c1, r1, c2 ) && vertical( r2, c2, r1, c2 ) )
				ok = true;
			// now we test point (r2, c1)
			if ( M[r2][c1] != '#' && vertical( r1, c1, r2, c1 ) && horizontal( r2, c2, r2, c1 ) )
				ok = true;
		}
		else {
			if ( r1 == r2 && horizontal( r1, c1, r2, c2 ) ){
				ok = true;
			}

			if ( c1 == c2 &&  vertical( r1, c1, r2, c2 ) ) {
				ok = true;
			}
		}
		puts( ok? "YES":"NO" );
	}  
	return 0;
}
