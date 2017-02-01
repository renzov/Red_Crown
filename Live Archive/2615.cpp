#include<cstdio>
#include<algorithm>
#include<climits>
#include<cstdlib>
#include<cassert>
#define X first
#define Y second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > point;

const int MAXN = 105;
point P[ 2 * MAXN ];
point O, I;

int area2( const point &A, const point &B, const point &C ){
	return (B.X - A.X)*(C.Y - A.Y) - (C.X - A.X)*(B.Y - A.Y);
}

bool left( const point &A, const point &B, const point &C ){
	return area2( A , B, C ) > 0;
}

bool cmp( const point &A, const point &B ){
	bool r1 = left( O , I , A );
	bool r2 = left( O , I , B );
	if ( r1 ^ r2 ) return r1;
	return left( O , A , B );
}

int main(){

	int N,B;
	int dp[ 2 ][ 2*MAXN ][ 2*MAXN ];
	int ch[ 2*MAXN ][ 2*MAXN ];
	int idx;

	while ( scanf("%d %d", &B, &N) && N ){
		scanf("%d %d", &O.X, &O.Y);
		N--;
		for ( int i=0; i < N; ++i )
			scanf("%d %d", &P[i].X, &P[i].Y);
		
		I = P[0];
		sort( P + 1 , P + N , cmp );

		for ( int i=0; i < N; ++i ) P[i + N] = P[i]; 
		
		int qp[ MAXN ];
		int qs[ MAXN ];
		int sz;
		int j;
		for ( int i=0; i < N; ++i ){
			ch[i][i] = INT_MAX;
			j = i + 1;
			sz = 0;
			// Init queues
			qs[ sz ] = 0, qp[ sz++ ] = i;
			while ( j < (i + N) && left( O , P[i] , P[j] ) ){
				while ( sz > 1 && !left( P[ qp[sz - 2] ] , P[ qp[sz - 1] ] , P[j] ) ){
					sz--;
				}
				qp[ sz ] = j;
				qs[ sz ] = qs[ sz - 1 ] + abs(area2( O , P[ qp[sz - 1] ] , P[j]  ));
				ch[i][j] = qs[ sz ];
				sz++,j++;
			}
			while ( j < i + N ){ 
				ch[i][j] = INT_MAX, j++;
			}
		}

	
		for ( int i=N; i < 2*N ; i++ ){
			ch[i][i] = INT_MAX;
			for ( j=i+1; j < 2*N; ++j )
				ch[i][j] = ch[i-N][j-N];
		}

		idx = 0;

		for ( int i=0; i < N; ++i )
			for ( int j=i; j < (i+N); ++j ){
				dp[idx][i][j] = ch[i][j];
			}

		for ( int b = 2; b <= B; ++b ){
			//Calculate dp[1-idx][i][j];
			for ( int i=0; i < N; ++i ){
				dp[1-idx][i][i] = INT_MAX;
				for ( j=i+1; j < (i+N); ++j ){
					dp[1-idx][i][j] = INT_MAX;
					int &ret = dp[1-idx][i][j];
					for ( int k=i+1; k < j; ++k ){
						if ( dp[idx][i][k] < INT_MAX && ch[k+1][j] < INT_MAX ){
							ret = min( ret , dp[idx][i][k] + ch[k+1][j] );
						}
					}
				}
			}
			idx = 1 - idx;
		}

		int res = INT_MAX;

		for ( int i=0; i < N; ++i )
			res = min( res , dp[idx][i][i+N-1] );

		if ( res & 1 ) printf("%d.50\n", (res >> 1));
		else printf("%d.00\n", res >> 1 );
		
	}
	return 0;
}

