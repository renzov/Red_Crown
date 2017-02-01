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

int dp[1<<19];

int solve(int state){
	if ( dp[state] != -1 ) return dp[state];
	if ( __builtin_popcount(state) == 1 ){
		return dp[state] = state;
	}
	int &ret = dp[state];
	ret = 0;
	int next,val;
	for ( int i=0; i < 19; ++i ){
		if ( (state>>i) & 1 ){
			next = state;
			val = i+2;
			for ( int j=i; j < 19; j += val ){
				if ((next>>j) & 1) next ^= (1<<j);
			}
			for ( int j=i; j < 19; j+= val ){
				for (int k=j+2; k < 19; k++){
					if ( ((next >> k)&1) && !((state >> (k-j-2))&1) )
						next ^= ( 1 << k );
				}
			}
			if ( solve( next ) == 0 ) ret |= (1<<i);
		}
	}
	return ret;
}

int main(){
    
    int num,n,ret,runs;
    int mask = -1;

    memset(dp, -1, sizeof(dp));
    scanf("%d",&runs);
    for ( int sce=1; sce <= runs; ++sce ){
        printf("Scenario #%d:\n",sce);
        mask = 0;        
        scanf("%d",&n);
        for( int i=0; i < n; ++i ){
            scanf("%d",&num);
            num -= 2;
            mask |= ( 1 << num );
        }
        ret = solve( mask );
        if ( !ret ){
            puts("There is no winning move.");
        }
        else {
            printf("The winning moves are:");
            for ( int i=0; i < 19; ++i ){
                if ( (ret>>i)&1 ) printf(" %d",i+2);
            }
            puts(".");
        }
        puts("");
    }
    return 0;
}

