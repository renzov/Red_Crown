#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
// Solution using D&C
const int MAXN = 500005;
int P[MAXN][3];
int sz[3];

void compress( const int &N, const int &dim ){
	vector<int> V(N);
	for ( int i = 0; i < N; ++i )
		V[i] = P[i][dim];
	
	sort( V.begin(), V.end() );
	int M = distance( V.begin(), unique( V.begin(), V.end() ) );
	V.resize(M);
	
	sz[dim] = M;
	for ( int i = 0; i < N; ++i )
		P[i][dim] = distance(  V.begin(), lower_bound( V.begin(), V.end(), P[i][dim] ) );
}

bool comp( const int &i, const int &j ){
	return P[ i ][ 1 ] < P[ j ][ 1 ];
}

vector<int> solve( const int &L, const int &R, vector<int> &idx ){
	if ( L == R ) // Every point in idx has the same X coordinate, so no domination between elements
		return idx;
	
	int M = ( L + R ) >> 1;
	// split into to lists of indices
	vector<int> left;
	vector<int> right;
	
	int u, v;
	for ( int i = 0; i < idx.size(); ++i ){
		u  = idx[i];
		if ( P[u][0] <= M ) left.push_back( u );
		else right.push_back( u );
	}
	
	if ( left.empty() ) return solve( M + 1, R, right );
	if ( right.empty() ) return solve( L, M, left ); 
	// In this case both parts are nonempty
	vector<int> leftSol = solve( L, M, left );
	vector<int> rightSol = solve( M + 1, R, right );

	// combine both solutions - need to check if point in the left is dominated by point in the right
	int i = 0;	// pointer in the left solution
	int j = 0;	// pointer in the right solution
	int Z = -1;	// max Z of the points in the right solution
	vector<int> sol;

	while ( i < leftSol.size() && j < rightSol.size() ){
		u = leftSol[i], v = rightSol[j];
		if ( P[u][1] >= P[v][1] ){
			if ( P[u][2] >= Z ) 
				sol.push_back(u);
			i++;
		}
		else {
			sol.push_back( v );
			Z = max( Z, P[v][2] );
			j++;
		}
	}
	while ( i < leftSol.size() ){
		u = leftSol[i];
		if ( P[u][2] >= Z ) // point is not dominated
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

	scanf("%d", &N);
	for ( int j = 0; j < 3; ++j )
		for ( int i = 0; i < N; ++i )
			scanf("%d", P[i] + j );
	
	// compress coordinates in each dimension
	for ( int j = 0; j < 3; ++j )
		compress( N, j );

	vector<int> ord(N);
	for ( int i = 0; i < N; ++i )
		ord[i] = i;

	sort( ord.begin(), ord.end(), comp );
	reverse( ord.begin(), ord.end() );
	
	vector<int> res = solve( 0, sz[0] - 1, ord );
	
	printf("%d\n", N - (int)res.size());
	return 0;
}

