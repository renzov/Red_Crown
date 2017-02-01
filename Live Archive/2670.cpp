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

int c[10];
int d[105];
int s[105];
int L[105][105];

int main(){
	int runs;

	scanf("%d",&runs);
	while ( runs-- ){
		memset( d , -1 , sizeof(d) );
		memset( s , 0 , sizeof(s) );
		for ( int i=0; i < 6 ; ++i ){
			scanf("%d",c+i);
			d[c[i]] = 1;
			L[ 1 ][ s[1]++ ] = c[i];
		}	
		int left = 94;
		int di = 2;
		int x,y;
		int z;
		while ( left > 0 ){
			for ( x = 1; x <= (di >> 1) ; ++x ){
				y = di - x;	
				for ( int i=0; i < s[x] ; ++i )
					for ( int j=0; j < s[y]; ++j ){
						z = L[x][i] + L[y][j];		
						if ( z <= 100 && d[z] == -1 ){
							d[z] = di;
							L[ di ][ s[di]++ ] = z;
							left--;
						}
						z = abs(L[x][i] - L[y][j]);
						if ( z > 0 && d[z] == -1 ){
							d[z] = di;
							L[di][ s[di]++ ] = z;
							left--;
						}
					}
			}
			di++;
		}
		int sum = 0;
		for ( int i=1; i <= 100; ++i ){
			sum += d[i];
		}
		printf("%d.%d %d\n",sum/100,sum%100,di - 1);
	}
	return 0;
}

