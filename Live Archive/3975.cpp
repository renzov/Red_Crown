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

const int MAXN = 10005;

int dx[] = {0,-1,0,1};
int dy[] = {1,0,-1,0};

int X[MAXN];
int Y[MAXN];
int N;
int R,C;
int xs,ys;
int xf,yf;

queue< pii > q;

int d[1005][1005];
int d2[1005][1005];

void bfs(){
	int x,y,nx,ny;

	while ( !q.empty() ){
		x = q.front().first;
		y = q.front().second;
		q.pop();
	
		for ( int k=0; k < 4; ++k ){
			nx = x + dx[k];
			ny = y + dy[k];
			if ( nx < 0 || nx >= R || ny < 0 || ny >= C ) continue;
			if ( d[nx][ny] == -1 ){
				d[nx][ny] = d[x][y] + 1;
				q.push( make_pair(nx,ny) );
			}
		}
	}
}

int bfs2( int lim ){
	int x,y,nx,ny;
	
	while ( !q.empty() ) q.pop();

	for ( int i=0; i < R; ++i )
		for ( int j = 0; j < C; ++j )
			d2[i][j] = -1;

	d2[xs][ys] = 0;
	q.push( make_pair(xs,ys) );

	while ( !q.empty() && d2[xf][yf] == -1 ){
		x = q.front().first;
		y = q.front().second;
		q.pop();

		for ( int k=0; k < 4; ++k ){
			nx = x + dx[k];
			ny = y + dy[k];
			if ( nx < 0 || nx >= R || ny < 0 || ny >= C ) continue;
			if  ( d[nx][ny] < lim ) 
				continue;

			if ( d2[nx][ny] == -1 ){
				d2[nx][ny] = d2[x][y] + 1;
				q.push( make_pair(nx,ny) );
			}
		}
	}
	return d2[xf][yf];
}

int main(){

	int runs;

	scanf("%d",&runs);
	while ( runs-- ){
		scanf("%d %d %d",&N,&R,&C);

		while ( !q.empty() ) q.pop();

		for ( int i=0; i < R; ++i )
			for (int j=0; j < C; ++j)
				d[i][j] = -1;

		scanf("%d %d %d %d",&xs,&ys,&xf,&yf);	
		
		for ( int i = 0; i < N; ++i ){
			scanf("%d %d",X+i,Y+i);
			q.push( make_pair( X[i] , Y[i] ) );
			d[ X[i] ][ Y[i] ] = 0;
		}

		bfs();

		int l = 0;
		int r = min( d[xs][ys] , d[xf][yf] ) + 1;
		int m;
		int res;
		int last = bfs2(0);

		while ( (r - l) > 1 ){
			m = ( l + r ) >> 1;
			res = bfs2(m);
			if ( res == -1 )
				r = m;
			else {
				l = m;
				last = res;
			}
		}
		printf("%d %d\n",l,last);
	}
	return 0;
}
