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

int dx[] = {1,0,-1,0};
int dy[] = {0,-1,0,1};
int n;
char M[15][15];
int B[15][15];

void update( int y, int x, int p ){
	int nx,ny;
	for ( int i=0; i < 4; ++i ){
		nx = x + dx[i];
		ny = y + dy[i];
		if ( nx < 0 || ny < 0 || nx >= n || ny >= n )
			continue;
		B[ ny ][ nx ] |= ( 1 << p );
	}
}

int main(){
	int runs;
	int b;
	scanf("%d",&runs);
	for ( int k=1; k<=runs; ++k ){
		printf("Case %d:\n",k);
		scanf("%d",&n);
		memset(B,0,sizeof(B));
		for ( int i=0; i < n; ++i ){
			for ( int j=0; j < n; ++j ){
				scanf(" %c",&M[i][j]);
				if ( M[i][j] != '.' )
					update( i , j , M[i][j] - 'A' );
			}
		}
		for ( int i=0; i < n; ++i ){
			for ( int j=0; j < n; ++j ){
				if ( M[i][j] != '.' ) continue;
				for ( b = 0; (B[i][j] >> b) & 1; ++b);
				M[i][j] = (char)( b + 'A' );
				update( i  , j , b );
			}
		}
		for ( int i=0; i < n; ++i ){
			for ( int j=0; j < n; ++j )
				putchar(M[i][j]);
			putchar('\n');
		}
	}
	return 0;
}

