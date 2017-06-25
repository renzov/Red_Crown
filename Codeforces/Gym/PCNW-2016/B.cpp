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

int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, -1, 0, 1 };

int N, M, L;
int sx, sy;
int ex, ey;
char G[64][64];
int dir[64];

int d[64][64][64];

inline int encode( const int &y, const int &x, const int &z ){
	return y | (x << 6) | (z << 12);
}

void decode( int st, int &y, int &x, int &z ){
	y = st & 0X3F; st >>= 6;
	x = st & 0X3F; st >>= 6;
	z = st & 0X3F;
}

inline bool valid( const int &y, const int &x ){
	return ( y >= 0 ) && ( y < N ) && ( x >= 0 ) && ( x < M ) && (G[y][x] == '.'); 
}

int solve(){
	//init the distance
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < M; ++j )
			for ( int k=0; k <= L; ++k )
				d[i][j][k] = INT_MAX;

	// Dijkstra using deque (0/1 BFS)
	d[sy][sx][0] = 0;
	deque<int> q;
	q.push_back( encode(sy, sx, 0) );
	int state;
	int x, y, z;
	int nx, ny, nz;
	while ( !q.empty() ){
		state = q.front();
		q.pop_front();
		decode( state, y, x, z );
		if ( x == ex && y == ey ) return d[y][x][z];
		// using a element of the string
		if ( z < L ){
			nx = x + dx[ dir[z] ];
			ny = y + dy[ dir[z] ];
			nz = z + 1;
			if ( !valid( ny, nx ) ){
				nx = x, ny = y;
			}
			if ( d[ny][nx][nz] > d[y][x][z] ){
				d[ny][nx][nz] = d[y][x][z];
				q.push_front( encode(ny, nx, nz) );
			}
		}
		// delete an element
		if ( z < L ){
			nx = x, ny = y, nz = z + 1;
			if ( d[ny][nx][nz] > ( d[y][x][z] + 1 ) ){
				d[ny][nx][nz] = d[y][x][z] + 1;
				q.push_back( encode(ny, nx, nz) );
			}
		}
		// add an element
		nz = z;
		for ( int i=0; i < 4; ++i ){
			nx = x + dx[i];
			ny = y + dy[i];
			if ( valid( ny, nx ) && (d[ny][nx][nz] > (d[y][x][z] + 1) ) ){
				d[ny][nx][nz] = d[y][x][z] + 1;
				q.push_back( encode( ny, nx, nz ) );
			}
		}
	}
	return -1;
}

int main(){
	char s[64];
	scanf("%d %d", &N, &M);
	// Read the grid
	for ( int i=0; i < N; ++i ){
		scanf("%s", G[i]);
		for ( int j=0; j < M; ++j ){
			if ( G[i][j] == 'R' ){
				sx = j, sy = i;
				G[i][j] = '.';
			}
			else if ( G[i][j] == 'E' ){
				ex = j, ey = i;
				G[i][j] = '.';
			}
		}
	}
	// Read and transform the command string
	scanf("%s", s);
	L = strlen(s);
	for ( int i=0; s[i]; ++i ){
		switch (s[i]){
			case 'L' : dir[i] = 2; break;
			case 'U' : dir[i] = 1; break;
			case 'R' : dir[i] = 0; break;
			case 'D' : dir[i] = 3; break;
		}
	}
	printf("%d\n", solve());
	return 0;
}

