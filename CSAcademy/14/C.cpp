#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <numeric>

#define repn( i , a , b ) for( int i = ( int ) a ; i < ( int ) b ; i ++ )
#define rep( i , n ) repn( i , 0 , n ) 
#define all( x )  x.begin() , x.end()
#define rall( x ) x.rbegin() , x.rend()
#define mp make_pair
#define fst first
#define snd second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

const int MAXN = 1024;
int mat[MAXN][MAXN];
int S[MAXN][MAXN];
int U[MAXN][MAXN];
int R[MAXN][MAXN];

inline int sum( const int &r1, const int &r2, const int &c1, const int &c2 ){
	return S[r2][c2] - S[r2][c1 - 1] - S[r1 - 1][c2] + S[r1 - 1][c1 - 1];
}

int main(){
	int N, M;
	int r1, r2, c1, c2;

	scanf("%d %d", &N, &M);
	
	for ( int i=1; i <= N; ++i )
		for ( int j=1; j <= M; ++j )
			scanf("%d", &mat[i][j]);

	for ( int i=1; i <= N; ++i )
		for ( int j=1; j <= M; ++j )
			S[i][j] = mat[i][j] + S[i][j - 1] + S[i - 1][j] - S[i-1][j - 1]; 
	
	for ( int i=1; i <= N; ++i ){
		for ( int j=1; j <= M; ++j ){
			if ( mat[i][j] ){
				U[i][j] = 1 + U[i - 1][j];
			}
		}
	}
	for ( int i=1; i <= N; ++i )
		for ( int j=M; j >= 1; --j )
			if ( mat[i][j] ){
				R[i][j] = 1 + R[i][j + 1];
			}

	int res = -1;
	int area;
	for ( int i=2; i < N; ++i )
		for ( int j=2; j < M; ++j ){
			if ( mat[i][j] ){
				r2 = i;
				r1 = i - U[i][j] + 1;
				c1 = j; 
				c2 = j + R[i][j] - 1;
				if ( r1 < 2 || c2 == M ) continue;
				area = (r2 - r1 + 1)*(c2 - c1 + 1);
				if ( sum(r1, r2, c1, c2) != area ) continue;
				if ( sum( r1 - 1, r2 + 1, c1 - 1, c2 + 1 ) != area ) continue;
				res = max( res , area );
			}
		}
	printf("%d\n", res);
	return 0;
}

