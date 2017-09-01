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

const int MAXW = 10005;
const int MAXD = 128;

int W, S;
int X, Y;
int P[MAXW][MAXD];
int O[MAXD] = {0};

int main(){
	int y;

	scanf("%d %d %d %d", &W, &S, &X, &Y);
	for ( int i=0; i < W; ++i )
		for ( int j=0; j < X; ++j )
			scanf("%d", &P[i][j]);
	
	for ( int i=0; i < S; ++i ){
		for ( int j=0; j < X; ++j ){
			scanf("%d", &y);
			O[j] = max( O[j], y ); 
		}
	}

	for ( int i=0; i < W; ++i ){
		for ( int j=0; j < X; ++j ){
			P[i][j] = min(Y - O[j], P[i][j]);
		}
		for ( int j=0; j < X; ++j ){
			if ( j ) putchar(' ');
			printf("%d", P[i][j]);
		}
		puts("");
	}
	return 0;
}

