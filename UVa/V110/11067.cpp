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
long long dp[105][105];
bool sure[105][105];

int w,h;

void init(){
	for ( int i=0; i <= h; ++i )
		for ( int j=0; j <= w; ++j ){
			dp[i][j] = 0LL;
			sure[i][j] = true;
		}
}

int main(){
	int n;
	int x,y;
	while ( scanf("%d %d",&w,&h) && h && w ){
		init();
		scanf("%d",&n);
		while ( n-- ){
			scanf("%d %d",&x,&y);
			if ( y <= h && x <= w )
				sure[y][x] = false;
		}

		dp[0][0] = 1;
		for ( int i=0; i <= h; ++i )
			for ( int j=0; j <= w; ++j ){
				if ( sure[i][j] ){
					if ( i > 0 ){
						dp[i][j] += dp[i-1][j];	
					}
					if ( j > 0 ){
						dp[i][j] += dp[i][j-1];
					}
				}
			}
		if ( dp[h][w] == 1 ){
			puts("There is one path from Little Red Riding Hood's house to her grandmother's house.");
		}
		else if ( dp[h][w] ){
			printf("There are %lld paths from Little Red Riding Hood's house to her grandmother's house.\n",dp[h][w]);
		}
		else {
			puts("There is no path.");
		}
	
	}

	return 0;
}

