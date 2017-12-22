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
#define X first
#define Y second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > point;

const int MAXN = 128;
int R, G;
int count_red[MAXN][MAXN];
int count_green[MAXN][MAXN];
int green[MAXN];
int red[MAXN];

point Pr[MAXN];
point Pb[MAXN];
point Pg[MAXN];

void read_points( point P[], const int &N ){
	for ( int i=0; i < N; ++i ) scanf("%d %d", &P[i].X, &P[i].Y);
}

bool left( const point &A, const point &B, const point &C ){
	return ( (B.X-A.X)*(C.Y-A.Y) - (C.X - A.X)*(B.Y - A.Y) ) > 0;
}

void count_below( const int &i, const int &j ){
	count_red[i][j] = 0;
	for ( int k=0; k < R; ++k ){
		if ( Pr[k].X >= Pb[i].X && Pr[k].X <= Pb[j].X && !left( Pb[i], Pb[j], Pr[k] ) )
			count_red[i][j]++;
	}
	count_red[j][i] = count_red[i][j];

	count_green[i][j] = 0;
	for ( int k=0; k < G; ++k ){
		if ( Pg[k].X >= Pb[i].X && Pg[k].X <= Pb[j].X && !left( Pb[i], Pb[j], Pg[k] ) )
			count_green[i][j]++;
	}
	count_green[j][i] = count_green[i][j];
}

int main(){
	int B;
	int cases = 0;
	while ( scanf("%d %d %d", &R, &G, &B) && ( R + G + B ) >= 0 ){
		read_points( Pr, R );
		read_points( Pg, G );
		read_points( Pb, B );
		
		sort( Pb, Pb + B );

		for ( int i=0; i < B; ++i )
			for ( int j=i+1; j < B; ++j )
				count_below( i , j );

		for ( int i=0; i < B; ++i ){
			red[i] = 0;
			for ( int j=0; j < R; ++j ){
				if ( Pb[i].X == Pr[j].X && Pr[j].Y < Pb[i].Y )
					red[i]++;
			}
			green[i] = 0;
			for ( int j=0; j < G; ++j ){
				if ( Pb[i].X == Pg[j].X && Pg[j].Y < Pb[i].Y )
					green[i]++;
			}
		}

		int red_tri = 0;
		int green_tri =0;
		int red_points;
		int green_points;

		for ( int i=0; i < B; ++i )
			for ( int j=i+1; j < B; ++j )
				for ( int k=j+1; k < B; ++k ){
					if ( left( Pb[i], Pb[k], Pb[j] ) ){
						red_points = count_red[i][j] + count_red[j][k] - count_red[i][k] - red[j]; 
						green_points = count_green[i][j] + count_green[j][k] - count_green[i][k] - green[j];
					}
					else {
						red_points = count_red[i][k] - count_red[i][j] - count_red[j][k] + red[j]; 
						green_points = count_green[i][k] - count_green[i][j] - count_green[j][k] + green[j];
					}
					if ( red_points > green_points ) red_tri++;
					if ( green_points > red_points ) green_tri++;	
				}

		printf("Case %d: %d %d\n", ++cases, red_tri, green_tri);
	}
	return 0;
}

