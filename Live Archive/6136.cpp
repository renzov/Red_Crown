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

const int LEFT = 3;
const int RIGHT = 1;
const int UP = 2;
const int DOWN = 0;

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
int R, C;
bool invalid[612][612][4] = {0};
bool vis[612][612] = {0};

inline bool inside( int x, int y ){
	return x >= 0 && x < R && y >= 0 && y < C;
}

void bfs( int x, int y ){
	queue< pii > q;
	q.push( pii(x,y) );

	int nx, ny;

	while ( !q.empty() ){
		x = q.front().X;
		y = q.front().Y;
		q.pop();

		for ( int i=0; i < 4; ++i ){
			if ( invalid[x][y][i] ) continue;
			nx = x + dx[i];
			ny = y + dy[i];
			if ( inside(nx,ny) && !vis[nx][ny] ){
				vis[nx][ny] = true;
				q.push( pii(nx, ny) );
			}
		}
	}
}

int main(){
	int N;
	char c;
	while ( scanf("%d", &N) != EOF ){
		R = 2*N, C = 2*N + 1;
		// Initializing adjacency matrix
		for ( int i=0; i < R; ++i )
			for ( int j=0; j < C; ++j ){
				invalid[i][j][0] = invalid[i][j][1] = invalid[i][j][2] = invalid[i][j][3] = false;
				vis[i][j] = false;
			}
		
		for ( int i=0; i < R - 1; ++i ){
			for ( int j = ( i&1 )? 1:0; j < C - 1; j += 2 ){
				scanf(" %c", &c);
				if ( c == 'H' ){
					invalid[i][j][DOWN] = invalid[i+1][j][UP] = true;
					invalid[i][j+1][DOWN] = invalid[i+1][j+1][UP] = true;
				}
				else {
					invalid[i][j][RIGHT] = invalid[i][j+1][LEFT] = true;
					invalid[i+1][j][RIGHT] = invalid[i+1][j+1][LEFT] = true;
				}
			}
		}
		
		int ncomp = 0;
		for ( int i=0; i < R; ++i )
			for ( int j=0; j < C; ++j )
				if ( !vis[i][j] ){
					vis[i][j] = true;
					bfs( i, j );
					ncomp++;
				}

		printf("%d\n", ncomp - 1);
	}
	return 0;
}

