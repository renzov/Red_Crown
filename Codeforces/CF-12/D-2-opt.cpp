#include<cstdio>
#include<vector>
#include<climits>
#include<algorithm>
#include<cassert>
using namespace std;
// Solution using D&C
const int MAXN = 500005;
int P[3][MAXN];	// to avoid cache miss
int sz[3];
int psum[MAXN];

inline int sum( const int &l, const int &r ){
	return l == 0? psum[r]:(psum[r] - psum[l - 1]);
}

void fastscan(int &number)
{
    //variable to indicate sign of input number
    bool negative = false;
    register int c;

    number = 0;

    // extract current character from buffer
    c = getchar();
    if (c=='-')
    {
        // number is negative
        negative = true;

        // extract the next character from the buffer
        c = getchar();
    }

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c>47 && c<58); c=getchar())
        number = number *10 + c - 48;

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
}

void compress( const int &N, const int &dim ){
	vector<int> V(N);
	for ( int i = 0; i < N; ++i )
		V[i] = P[dim][i];
	
	sort( V.begin(), V.end() );
	int M = distance( V.begin(), unique( V.begin(), V.end() ) );
	V.resize(M);
	
	sz[dim] = M;
	for ( int i = 0; i < N; ++i )
		P[dim][i] = distance(  V.begin(), lower_bound( V.begin(), V.end(), P[dim][i] ) );
}

bool comp( const int &i, const int &j ){
	return P[ 1 ][ i ] < P[ 1 ][ j ];
}

vector<int> solve( const int &L, const int &R, vector<int> &idx ){
	if ( L == R ) // Every point in idx has the same X coordinate, so no domination between elements
		return idx;

	int M = ( L + R ) >> 1;
	int A = sum( L, M );
	int B = sum( M + 1, R );
	
	if ( !B ) return solve( L, M, idx ); 
	if ( !A ) return solve( M + 1, R, idx );

	// split into to lists of indices
	vector<int> left(A);
	vector<int> right(B);
	
	int u, v;
	int i = 0;	// pointer for left part
	int j = 0; // pointer for right part

	for ( int k = 0; k < (int)idx.size(); ++k ){
		u  = idx[k];
		if ( P[0][u] <= M ) left[i++] = u;
		else right[j++] = u;
		assert( i <= A );
		assert( j <= B );
	}
	// In this case both parts are nonempty
	vector<int> leftSol = solve( L, M, left );
	vector<int> rightSol = solve( M + 1, R, right );

	// combine both solutions - need to check if point in the left is dominated by point in the right
	i = 0;	// pointer in the left solution
	j = 0;	// pointer in the right solution
	int Z = -1;	// max Z of the points in the right solution
	vector<int> sol;
	sol.reserve( (int)rightSol.size() );

	while ( i < leftSol.size() && j < rightSol.size() ){
		u = leftSol[i], v = rightSol[j];
		if ( P[1][u] >= P[1][v] ){
			if ( P[2][u] >= Z ) 
				sol.push_back(u);
			i++;
		}
		else {
			sol.push_back( v );
			Z = max( Z, P[2][v] );
			j++;
		}
	}
	while ( i < leftSol.size() ){
		u = leftSol[i];
		if ( P[2][u] >= Z ) // point is not dominated
			sol.push_back( u ); 
		i++;
	}
	while ( j < rightSol.size() ){
		sol.push_back( rightSol[j] );
		j++;
	}
	return sol;
}

int main(){
	int N;

	fastscan( N );
	for ( int j = 0; j < 3; ++j )
		for ( int i = 0; i < N; ++i )
			fastscan( P[j][i] );
	
	// compress coordinates in each dimension
	for ( int j = 0; j < 3; ++j )
		compress( N, j );

	// calculate partial sums for X	
	for ( int i = 0; i < N; ++i )
		psum[ P[0][i] ]++;
	for ( int i = 1; i < sz[0]; ++i )
		psum[i] += psum[i - 1];

	vector<int> ord(N);
	for ( int i = 0; i < N; ++i )
		ord[i] = i;

	sort( ord.begin(), ord.end(), comp );
	reverse( ord.begin(), ord.end() );
	
	vector<int> res = solve( 0, sz[0] - 1, ord );
	
	printf("%d\n", N - (int)res.size());
	return 0;
}
