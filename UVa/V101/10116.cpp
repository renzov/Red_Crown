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

int n,m;
int sy;
int M[100][100];
int d[100][100];


int dx[] = {0,-1,0,1};
int dy[] = {1,0,-1,0};

int direc( char c ){
	switch ( c ){
		case 'N' : return 1;
		case 'S' : return 3;
		case 'E' : return 0;
		case 'W' : return 2;
	}
}

bool valid( int x , int y ){
	return (x >= 0) && (y >= 0) && (x < n) && (y < m);
}

void process(){

	memset( d , -1, sizeof(d) );

	d[ 0 ][ sy ] = 0;

	int x , y;
	int nx,ny;
	
	x = 0;
	y = sy;

	while ( 1 ){
		nx = x + dx[ M[x][y] ];
		ny = y + dy[ M[x][y] ];

		if ( !valid( nx , ny ) ){
			printf("%d step(s) to exit\n",d[x][y] + 1);
			break;
		}
		if ( d[nx][ny] != -1 ){
			printf("%d step(s) before a loop of %d step(s)\n",d[nx][ny] - d[0][sy] , d[x][y] - d[nx][ny] + 1 );
			break;
		}
		d[nx][ny] = d[x][y] + 1;
		x = nx;
		y = ny;
	}
}

int main(){
	char c;
	while ( scanf("%d %d %d",&n,&m,&sy) && ( sy || n || m ) ){
		sy--;
		for ( int i=0; i < n; ++i ){
			for ( int j=0; j < m; ++j ){
				scanf(" %c",&c);
				M[i][j] = direc(c);
			}
		}
		process();
	}
	return 0;
}

