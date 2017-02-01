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
#include <climits>

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
const int MAXD = 1005;

int X[MAXD];
int Y[MAXD];
int XY[MAXD][MAXD];

int main(){

	int N,D;
	int x,y;
	int runs;

	scanf("%d",&runs);
	while ( runs-- ){
		scanf("%d %d",&D,&N);

		for ( int i=0; i < D; ++i ){
			X[i] = Y[i] = 0;
			for ( int j=0; j < D; ++j )
				XY[i][j] = 0;
		}

		for ( int i=0; i < N; ++i ){
			scanf("%d %d",&x,&y);
			x = (x%D + D) % D;
			y = (y%D + D) % D; 
			X[x]++;
			Y[y]++;
			XY[x][y]++;
		}

		int res = INT_MAX;

		for ( int i=0; i < D; ++i )
			for ( int j=0; j < D; ++j )
				res = min( res , X[i] + Y[j] - XY[i][j] );

		printf("%d\n",res);
	}
	return 0;
}

