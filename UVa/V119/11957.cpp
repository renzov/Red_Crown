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
const int MOD = 1000007;
int n;
char M[105][105];
int dp[105][105];
bool reach[105][105];

int di[]={ -1 , -1 };
int dj[]={  1 , -1 };

bool valid( int i, int j ){
	if ( i < 0 || j < 0 || i >= n || j >= n ) return false;
	return M[i][j] != 'B';
}

int main(){
	
	int runs;
	scanf("%d",&runs);
	for ( int r=1; r <= runs ; ++r ){
		scanf("%d",&n);
		for ( int i=0; i < n; ++i ){
			for ( int j=0; j < n; ++j ){
				scanf(" %c",&M[i][j]);
				dp[i][j] = 0;
				reach[i][j] = false;
				if ( M[i][j] == 'W' ){
					dp[i][j] = 1;
					reach[i][j] = true;
				}
			}
		}
		int ni,nj;
		for ( int i=n-1; i > 0 ; --i ){
			for ( int j=n - 1; j >= 0 ; --j ){
				if ( reach[i][j] ){
					for ( int k=0; k < 2; ++k ){
						ni = i + di[k];
						nj = j + dj[k];
						if ( valid( ni , nj ) ){
							dp[ni][nj] += dp[i][j];
							dp[ni][nj] %= MOD;
							reach[ni][nj] = true;
						}
						else {
							ni = i + 2*di[k];
							nj = j + 2*dj[k];
							if ( valid( ni , nj ) ){
								dp[ni][nj] += dp[i][j];
								dp[ni][nj] %= MOD;
								reach[ni][nj] = true;
							}
						}
					}
				}
			}
		}
		int res = 0;
		for ( int i=0; i < n; ++i ){
			res += dp[0][i];
			res %= MOD;
		}
		printf("Case %d: %d\n",r,res);
	}
	return 0;
}

