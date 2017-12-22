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
#define X first
#define Y second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;
typedef pair< int , pii > node;

const int MAXH = 505;
char M[MAXH][MAXH];
int d[MAXH][MAXH];
int H, W, D;
int sx, sy;
int dx[] = {0, -1, 0, 1};
int dy[] = {1, 0, -1, 0};

inline bool valid( const int &x, const int &y ){
	return x >= 0 && x < H && y >= 0 && y < W && M[x][y] != '#';
}

int dijkstra(){
	// init distance matrix
	for ( int i=0; i < H; ++i )
		for ( int j=0; j < W; ++j )
			d[i][j] = INT_MAX;
	d[sx][sy] = 0;

	priority_queue< node, vector<node>, greater<node> > q;
	q.push( node( 0, pii(sx, sy) ) );
	
	int x, y, w;
	int nx, ny;
	while ( !q.empty() ){
		w = q.top().X;
		x = q.top().Y.X;
		y = q.top().Y.Y;
		q.pop();
		if ( w > d[x][y] ) continue;
		if ( x == 0 || x == (H-1) || y == 0 || y == (W-1) ) return d[x][y];
		for ( int i=0; i < 4; ++i ){
			nx = x + dx[i], ny = y + dy[i];
			if ( valid(nx, ny) ){
				if ( M[nx][ny] == '.' ){
					if ( w + 1 < d[nx][ny] ){
						d[nx][ny] = w + 1;
						q.push( node( w + 1, pii(nx, ny) ) );
					}
				}
				else {
					if ( w + D + 1 < d[nx][ny] ){
						d[nx][ny] = w + D  + 1;
						q.push( node( w + D + 1, pii(nx, ny) ) );
					}
				}
			}
		}
	}
	return -1;
}

int main(){

	int runs;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d %d", &H, &W, &D);
		for ( int i=0; i < H; ++i ){
			scanf("%s", M[i]);
			for ( int j=0; j < W; ++j ){
				if ( M[i][j] == 'S' ) sx = i, sy = j;
			}
		}
		M[sx][sy] = '.';
		printf("%d\n", dijkstra() + 1);
	}
	return 0;
}

