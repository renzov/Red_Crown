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

int d[ 65 ][ 65 ][ 65 ];
int p[ 65 ][ 65 ][ 65 ];

struct triple{
	int x,y,z;
	triple(int X,int Y,int Z){
		x = X,y = Y,z = Z;
	}
	triple();
};

void bfs( int s ){

	queue< triple  > q;

	d[s][s][s] = 0;
	q.push( triple(s,s,s) );

	int a[4];
	int b[4];
	int k;
	while ( !q.empty() ){
		a[1] = q.front().x;
		a[2] = q.front().y;
		a[3] = q.front().z;		
		q.pop();
		for ( int i=1; i <= 3; ++i ){
			if ( !(a[i] & 1) ){
				for ( int j=1; j <= 3; ++j ){
					if ( i != j ){
						b[i] = a[i] >> 1;
						b[j] = a[j] + b[i];
						k = i ^ j;
						b[ k ] = a[ k ];
						if ( d[b[1]][b[2]][b[3]] == -1 ){
							d[ b[1] ][ b[2] ][ b[3] ] = d[a[1]][a[2]][a[3]] + 1;
							p[b[1]][b[2]][b[3]] = a[1] | ( a[2] << 6 ) | (a[3] << 12);
							q.push( triple(b[1],b[2],b[3]) );
						}
					}
				}
			
			}
		}
	}
}

void print( int x , int y , int z ){
	printf("%4d%4d%4d\n",x,y,z);
	if ( x != y || x != z ){
		int a[4];
		int s = p[x][y][z];
		for ( int i=1; i <= 3; ++i ){
			a[ i ] = ( s & 63);
			s >>= 6;
		}
		print( a[1] , a[2] , a[3] );
	}
}

int main(){

	memset( d , -1 , sizeof(d) );
	d[0][0][0] = 0;
	for ( int i=1; i <= 20 ; ++i ){
		bfs(i);
	}
	int x,y,z;
	while ( scanf("%d %d %d",&x,&y,&z) == 3 ){
		if ( d[x][y][z] != -1 )
			print(x,y,z);
		else 
			printf("%4d%4d%4d\n",x,y,z);
		puts("============");
	}

	return 0;
}

