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

const int MAXN = 105;

double dp[MAXN][MAXN];
int test[MAXN][MAXN] = {0};
int X[MAXN];
int Y[MAXN];
int N,b1,b2;
double D[MAXN][MAXN];
int cases;
bool side[MAXN][MAXN];

int sA,sB;
int solA[MAXN];
int solB[MAXN];



double Distance( int a, int b ){
	return sqrt( 1.0*(X[a]-X[b])*(X[a]-X[b]) + (Y[a]-Y[b])*(Y[a]-Y[b]) );
}

double solve( int x, int y ){
	int next = max( x , y ) + 1;

	if ( next == (N-1) )
		return D[x][N-1] + D[y][N-1];
	
	if ( test[x][y] == cases ) return dp[x][y];
	
	test[x][y] = cases;
	double &res = dp[x][y];

	if ( next == b1 ){
		side[x][y] = false;
		res = solve( next , y ) + D[x][next];
	}
	else if ( next == b2 ){
		side[x][y] = true;
		res = solve( x , next ) + D[y][next];
	}
	else {
		double A = solve( next , y ) + D[x][next];
		double B = solve( x , next ) + D[y][next];
		if ( A <= B ){
			side[x][y] = false;
			res = A;
		}
		else {
			side[x][y] = true;
			res = B;
		}
	}
	return res;
}

void get_sol( int x,  int y ){
	int next = max( x , y ) + 1;
	if ( next == (N-1)) return;
	if ( side[x][y] ){
		solB[sB++] = next;
		get_sol( x , next );
	}
	else {
		solA[sA++] = next;
		get_sol( next, y );
	}
}

int main(){
	double res;
	cases = 0;
	while ( scanf("%d %d %d", &N, &b1, &b2) && N ){
		cases++;
		for ( int i=0; i<N; ++i ){
			scanf("%d %d", X+i, Y+i );
		}
		for ( int i=0; i < N; ++i ){
			D[i][i] = 0.0;
			for ( int j=0; j < i; ++j ){
				D[i][j] = D[j][i] = Distance( i , j );
			}
		}
		sA = sB = 0; 
		res = solve( 0 , 0 );
		printf("Case %d: %0.2f\n", cases, res);
		get_sol( 0  , 0 );

		printf("0");
		if ( solA[0] == 1 ){
			for ( int i=0; i < sA; ++i )
				printf(" %d", solA[i]);
			printf(" %d", N - 1 );
			for ( int i=sB-1; i >= 0; --i )
				printf(" %d", solB[i]);
		}
		else {
			for ( int i=0; i < sB; ++i )
				printf(" %d", solB[i]);
			printf(" %d", N-1);
			for ( int i=sA-1; i >= 0 ; --i )
				printf(" %d", solA[i]);
		}
		puts(" 0");
	}
	return 0;
}

