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
int X[MAXN], Y[MAXN];
typedef pair< int, pii > point;
set<point> T; // for triangle triples 

int M[256][256]; // Map from point to index in input
int triple[3];	

int dist2( const int &i, const int &j ){
	return (X[i] - X[j])*(X[i] - X[j]) + (Y[i] - Y[j])*(Y[i] - Y[j]);
}

void test( const int &i, const int &j, const int &TA2, const int &TB2, const int &TC2 ){
	long long A2 = dist2( i , j );
	
	if ( (TB2*A2) % TA2 || (TC2*A2) % TA2 ) return;

	/*
		Find the third point using law of cosines
		C2 = A2 + B2 - ABcos(theta) 
	*/

	long long B2 = TB2*A2 / TA2;
	long long C2 = TC2*A2 / TA2;
	long long cos2num = A2 + B2 - C2;
	long long sin2num = 4*A2*B2 - cos2num*cos2num;
	
	long long root = sqrt( (double)sin2num );
	if ( (root+1)*(root+1) <= sin2num ) root++;
	if ( root*root != sin2num ) return;

	long long X1 = X[i], X2 = X[j];
	long long Y1 = Y[i], Y2 = Y[j];
	long long X3, Y3;

	long long num = cos2num * ( X2 - X1 ) - root * ( Y2 - Y1 );
	long long den = 2*A2;
	if ( num % den ) return;

	X3 = X1 + num / den;

	num = cos2num * ( Y2 - Y1 ) + root * ( X2 - X1 );
	if ( num % den ) return;

	Y3 = Y1 + num / den;

	if ( X3 <= 100 && X3 >= -100 && Y3 <= 100 && Y3 >= -100 && M[X3+100][Y3+100] >= 0 ){
		triple[0] = i, triple[1] = j, triple[2] = M[X3+100][Y3+100];
		sort( triple, triple+3 );
		T.insert( point( triple[0], pii(triple[1], triple[2]) ) );
	}
}

int main(){
	long long TA2, TB2, TC2;
	int N;
	while ( scanf("%d", &N) != EOF ){
		// Clean memory for testcase
		T.clear();
		for ( int i=0; i < 256; ++i )
			fill( M[i], M[i] + 256, -1 );
		// Read input 
		for ( int i=0; i < N; ++i ){ 
			scanf("%d %d", X+i, Y+i);
			M[ X[i] + 100 ][ Y[i] + 100 ] = i;
		}
		// Square of sides of triangle
		TA2 = dist2(0,1);
		TB2 = dist2(1,2);
		TC2 = dist2(0,2);
		// Testing every pair of points as A side
		for ( int i=0; i < N; ++i )
			for ( int j=0; j < N; ++j ){
				if ( i != j ){
					test( i , j , TA2, TB2, TC2 );
					test( i , j , TA2, TC2, TB2 );
				}
			}

		printf("%d\n", (int)T.size() );
	}

	return 0;
}

