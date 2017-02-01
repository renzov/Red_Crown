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

struct triple{
	int x,y,z;
	triple(){}
	triple(int xx,int yy,int zz){ x = xx; y = yy; z = zz; }
};

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

int X;
int n,m;
char M[25][55][55];
int d[25][55][55];
int ex,ey;
int sx,sy;

int dx[]={0,-1,0,1,0};
int dy[]={1,0,-1,0,0};

int bfs(){
	int x,y,z,nz,ny,nx;
	queue< triple > q;

	for ( int i=0; i<n; ++i )
		for (int j=0; j < m; ++j)
			for ( int k=0; k < m; ++k )
				d[i][j][k] = -1;
	
	d[sx][sy][0] = 0;
	q.push( triple(sx,sy,0) );
	
	while ( !q.empty() ){
		x = q.front().x;
		y = q.front().y;
		z = q.front().z;
		q.pop();
		//printf("visit -> %d %d %d\n",x,y,z);
		if ( x == ex && y == ey ) return d[x][y][z];
		if ( d[x][y][z] >= X ) continue;
		nz = (z+1)%m;
		for ( int i=0; i < 5; ++i ){
			nx = x + dx[i];
			ny = y + dy[i];
			if ( nx < 0 || nx >= n || ny < 0 || ny >= m ) continue;
			if ( M[nx][ny][nz] != 'O' ) continue;
			if ( d[nx][ny][nz] == -1 ){
				q.push( triple(nx,ny,nz) );
				d[nx][ny][nz] = d[x][y][z] + 1;
			}
		}
	}
	return -1;
}

void precalc_scenario(){
	char right;
	for ( int k=1; k < m; ++k){
		right = 1;
		for ( int i=n-2; i > 0; --i ){
			for ( int j=0; j < m; ++j ){
				if ( right ){
					M[i][j][k] = M[i][(m+j-1)%m][k-1];
				}
				else {
					M[i][j][k] = M[i][(j+1)%m][k-1];
				}
			}
			right ^= 1;
		}
	}
	for ( int k=1; k < m; ++k ){
		for ( int j=0; j < m; ++j ){
			M[0][j][k] = M[0][j][k-1];
			M[n-1][j][k] = M[n-1][j][k-1];
		}
	}
}

int main(){
	int res;
	int runs;
	scanf("%d",&runs);
	while ( runs-- ){
		scanf("%d",&X);
		scanf("%d %d",&n,&m);
		n+=2;
		for ( int i=0; i < n; ++i ){
			for ( int j=0; j < m; ++j ){
				scanf(" %c",&M[i][j][0]);
				if ( M[i][j][0] == 'G' ){
					ex = i; ey = j;
					M[i][j][0] = 'O';
				}
				else if ( M[i][j][0] == 'F' ){
					sx = i; sy = j;
					M[i][j][0] = 'O';
				}
			}
		}
		precalc_scenario();
		//printf("Run %d\n\n",runs);
		//for ( int k=0; k<m; ++k ){
		//	for ( int i=0; i < n; ++i ){
		//		for ( int j=0; j < m; ++j ){
		//			printf("%c",M[i][j][k]);		
		//		}
		//		putchar('\n');
		//	}
		//	puts("");
		//}
		res = bfs();
		if ( res != -1 ) printf("The minimum number of turns is %d.\n",res);
		else puts("The problem has no solution.");
	}
	return 0;
}

