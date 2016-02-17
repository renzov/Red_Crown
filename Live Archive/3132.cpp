#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <climits>
#define X first
#define Y second
using namespace std;
typedef pair< int , int > point;

const int MAXN = 54;

int N;
point P[MAXN << 1];
bool D[MAXN][MAXN];

int area2( int i, int j, int k ){
	return abs ( (P[j].X - P[i].X)*(P[k].Y - P[i].Y) 
			- (P[k].X - P[i].X)*(P[j].Y - P[i].Y) );
}

int sarea2( int i, int j, int k ){
	return (P[j].X - P[i].X)*(P[k].Y - P[i].Y) 
			- (P[k].X - P[i].X)*(P[j].Y - P[i].Y);
}


bool left_st( int i, int j , int k ){
	return ((P[j].X - P[i].X)*(P[k].Y - P[i].Y) 
			- (P[k].X - P[i].X)*(P[j].Y - P[i].Y)) > 0;
}

bool left( int i , int j , int k ){
	return ((P[j].X - P[i].X)*(P[k].Y - P[i].Y) 
			- (P[k].X - P[i].X)*(P[j].Y - P[i].Y)) >= 0;
}

bool colinear( int i, int j, int k ){
	return ((P[j].X - P[i].X)*(P[k].Y - P[i].Y) 
			- (P[k].X - P[i].X)*(P[j].Y - P[i].Y)) == 0;
}

bool inter_prop( int i, int j, int k, int l ){
	if (colinear(i,j,k) || colinear(i,j,l) ||
	    colinear(k,l,i) || colinear(k,l,j) )
		return false;
	return	( left_st(i,j,k) ^ left_st(i,j,l) ) &&
			( left_st(k,l,i) ^ left_st(k,l,j) );
}

bool between(int i, int j, int k){
	if (!colinear(i,j,k)) return false;
	if (P[i].X != P[j].X) 
		return 	(P[i].X <= P[k].X && P[k].X <= P[j].X) ||
				(P[j].X <= P[k].X && P[k].X <= P[i].X);
	return 	(P[i].Y <= P[k].Y && P[k].Y <= P[j].Y) ||
			(P[j].Y <= P[k].Y && P[k].Y <= P[i].Y);

}

bool intersect( int i , int j, int k, int l ){
	return inter_prop(i,j,k,l) || 
	( between(i,j,k) || between(i,j,l) || between(k,l,i) || between(k,l,j) ); 
}

bool noInterPoly( int i, int j ){
	int l;
	for ( int k=0; k < (N-1); ++k ){
		l = k + 1;
		if ( k != i && k != j && l != i 
		     && l != j && intersect(i,j,k,l) ){
			 return false;
		}
	}
	if ( i != (N-1) && j != (N-1) && 
		 i != 0 && j != 0 ) 
		return !intersect(i,j,N-1,0); 
	return true;
}

bool inCone( int i , int j ){
	int u = (i > 0)? (i-1):(N-1);
	int w = (i < (N-1))? (i+1):0; 
	if ( left(i, w,  u) ){
		return left_st(i,j,u) && left_st(j,i,w);
	}
	else {
		return !(left(i,j,w) && left(j,i,u));
	}
}

bool isDiagonal( int i , int j ){
	return inCone( i , j ) && inCone( j , i ) && noInterPoly( i , j );
}

int dp[MAXN << 1][MAXN << 1 ];

int main(){
	int runs;
	int x, y;
	int k, a, b;

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &N);
		for ( int i=0; i < N; ++i ){
			scanf("%d %d", &x, &y);
			P[i] = make_pair(x,y);
		}
		int sum = 0;
		for (int i=1; i < (N-1); ++i)
			sum += sarea2(0, i, i+1);
		
		if ( sum < 0 ){
			reverse(P, P + N);
		}
		for ( int i=0; i < N; ++i ) P[i+N] = P[i];


		for ( int i=0; i < N; ++i ){
			D[i][i] = false;
			for ( int j=i+2; j < N; ++j ){
				D[i][j] = D[j][i] = isDiagonal( i , j );
			}
		}

		for ( int i=0; i < (N-1); ++i ) D[i][i+1] = D[i+1][i] = true;
		D[0][N-1] = D[N-1][0] = true;

		for ( int i=0; i < (N << 1) ; ++i ){
			for ( int j=0; j < (N << 1); ++j )
				dp[i][j] = INT_MAX;
			dp[i][i] = dp[i][i+1] = 0;
		}

		for ( int L=2; L < N ; ++L ){
			for ( int i=0; i < N; ++i ){
				k = i + L;
				int &ret = dp[i][k];
				for ( int j=i+1; j < k; ++j ){
					a = ( j < N )? j:j-N;
					b = ( k < N )? k:k-N;
					if ( D[i][a] && D[a][b] && D[i][b] ){
						ret = min( ret , max( dp[i][j] , max( dp[j][k] , area2( i, k, j ) ) ) ); 
					}
				}
			}
		}
		
		int res = INT_MAX;
		for ( int i=0; i < N ; ++i ){
			res = min( res , dp[i][i+N-1] );
		}
		printf("%d.%d\n", res/2 , 5*(res&1) );
	}
	return 0;
}
