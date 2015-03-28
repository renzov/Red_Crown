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

int dx[] = {0,-1,0,1};
int dy[] = {1,0,-1,0};

int M[1005][1005];
int W,H;
int sx,sy;
int tx,ty;

void bfs( int xi, int yi, int d[1005][1005] ){
	queue<pii> q;
	for ( int i=0; i < H; ++i )
		for ( int j=0; j < W; ++j )
			d[i][j] = -1;
	d[xi][yi] = 0;
	q.push( make_pair(xi,yi) );
	int x,y,nx,ny;
	while ( !q.empty() ){
		x = q.front().first;
		y = q.front().second;
		q.pop();
		for ( int k=0; k < 4; ++k ){
			nx = x + dx[k];
			ny = y + dy[k];
			if ( nx < 0 || ny < 0 || nx >= H || ny >= W ||
			    M[nx][ny] == 1) 
					continue;
			if ( d[nx][ny] == -1 ){
				d[nx][ny] = d[x][y] + 1;
				q.push( make_pair(nx,ny) );
			}
		}
	}
}

int main(){
	int res;
	scanf("%d %d",&W,&H);	

	for ( int i=0; i < H; ++i )
		for ( int j=0; j < W; ++j ){
			scanf("%d",&M[i][j]);
			if (M[i][j] == 2){ sx = i, sy = j; }
			if (M[i][j] == 3){ tx = i, ty = j; }
		}
		
	int d1[1005][1005];
	int d2[1005][1005];

	M[tx][ty] = 1;
	bfs(sx,sy,d1);
	M[tx][ty] = 3;
	bfs(tx,ty,d2);
	
	res = INT_MAX;

	for ( int i=0; i < H; ++i )
		for ( int j=0; j < W; ++j ){
			if ( M[i][j] == 4 && d1[i][j] > -1 && d2[i][j] > -1 ){
				res = min( res , d1[i][j] + d2[i][j] );
			}
		}
	printf("%d\n",res);
	return 0;
}

