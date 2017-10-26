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
typedef pair< int , int > pii;

const int MAXR = 55;

int R, C;
char M[MAXR][MAXR];
int vis[MAXR][MAXR];
pii match[ MAXR ][ MAXR ]; 
bool ismatch[MAXR][MAXR];
int tim;

int dx[] = {1, 0, -1, 0};
int dy[] = {0, -1, 0, 1};

inline bool isvalid( const int &x, const int &y ){
	return x >= 0 && x < R && y >= 0 && y < C && M[x][y] == '.'; 
}

bool alt_path( int ux, int uy ){
	if ( vis[ux][uy] >= tim ) return false;
	vis[ux][uy] = tim;
	int vx, vy;
	for ( int i=0; i < 4; ++i ){
		vx = ux + dx[i];
		vy = uy + dy[i];
		if ( !isvalid(vx, vy) ) continue;
		if ( !ismatch[vx][vy] || alt_path( match[vx][vy].X, match[vx][vy].Y ) ){
			ismatch[vx][vy] = true;
			match[vx][vy].X = ux, match[vx][vy].Y = uy;
			return true;
		}
	}
	return false;
}

int main(){

	while ( scanf("%d %d", &R, &C) != EOF ){
		for ( int i=0; i < R; ++i ){
			scanf("%s", M[i]);
		}
		
		for ( int i=0; i < R; ++i ){
			for ( int j=0; j < C; ++j ){
				ismatch[i][j] = false;
				vis[i][j] = -1;
			}
		}
		
		int cntW = 0; 
		int cntB = 0;
		int cntM = 0;
		bool ok = true;
		tim = 0;

		for ( int i=0; ok && i < R; ++i )
			for ( int j=0; ok && j < C; ++j ){
				if ( M[i][j] == '.' ){
					if ( (i + j) & 1 ){ 
						cntW++;
					}
					else { 
						cntB++;
						if ( alt_path( i , j ) ){
							cntM++;
						}
						else {
							ok = false;
						}
						tim++;
					}
				}
			}

		if ( !ok || cntM != cntW ) puts("1");
		else puts("2");
	}
	return 0;
}

