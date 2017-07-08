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

const int MAXN = 4096;
int T = 0;
int N, E, S;
int L[MAXN], R[MAXN];
int r, l;
int X[MAXN], Y[MAXN];

double dp[MAXN][MAXN][2];
int tm[MAXN][MAXN][2] = {0};

double dist( const int &i, const int &j ){
	return sqrt ( (double)( X[i] - X[j] )*( X[i] - X[j] ) + (double)( Y[i] - Y[j] )*( Y[i] - Y[j] ) );
}

double solve( int i, int j, int lf ){
	if ( i == l-2 && j == r-2 ) {
		return (lf==0) ? dist(L[i], L[i+1]):dist(R[j], R[j+1]);
	}
	if ( tm[i][j][lf] < T ){
		tm[i][j][lf] = T;
		dp[i][j][lf] = 1e20;
		if ( i < l - 2 ){
			if ( lf == 0 ){
				dp[i][j][lf] = min( dp[i][j][lf], dist(L[i], L[i+1]) + solve( i+1, j, 0 ) );
			}
			else {
				dp[i][j][lf] = min( dp[i][j][lf], dist(R[j], L[i+1]) + solve( i+1, j, 0 ) );			
			}
		}
		if ( j < r - 2 ){
			if ( lf == 0 ){
				dp[i][j][lf] = min( dp[i][j][lf], dist(L[i], R[j+1]) + solve( i, j+1, 1 ) );			
			}
			else {
				dp[i][j][lf] = min( dp[i][j][lf], dist(R[j], R[j+1]) + solve( i, j+1, 1 ) );			
			}
		}
	}
	return dp[i][j][lf];
}

int main(){
	while ( scanf("%d %d %d", &N, &E, &S) != EOF ){
		E--, S--;
		T++;

		if ( E > S ) swap(E,S);
		r = l = 0;
		for ( int i=E; i <= S; ++i ) R[r++] = i;
		for ( int i=S; i <= N+E; ++i ) L[l++] = i % N;
		reverse( L, L + l );

		for ( int i=0; i < N; ++i ) scanf("%d %d", X+i, Y+i);
		
		printf("%.6f\n", solve(0,0,0));	
	}
	return 0;
}

