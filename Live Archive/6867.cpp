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

const int MAXW = 55;
const int MAXK = 105;
const int MAXN = 303;

int p[MAXW][MAXK];
int t[MAXW][MAXK];
int size[MAXW];
int dp[MAXW][MAXN];
int price[MAXW][MAXN];

int main(){
	int s,c;
	int N,W;

	while ( scanf("%d %d",&N,&W) != EOF ){
		W++;
		for ( int i=W-1; i >= 0; i-- ){
			scanf("%d",size + i);
			for ( int j=0; j < size[i]; ++j ){
				scanf("%d", &p[i][j]);
			}
			for (int j=0; j < size[i]; ++j){
				scanf("%d",&t[i][j]);
			}
		}
		
		for ( int i=0; i < W; ++i ){
			dp[i][0] = 0;
			price[i][0] = 5000;
			for (int j=1; j <= N; ++j ){
				dp[i][j] = dp[i][j-1];
				price[i][j] = 5000;
				for ( int k=0; k < size[i]; ++k ){
					c = min( j , t[i][k] );
					s = (i > 0)? dp[i-1][j-c]:0;
					if ( dp[i][j] < (s + c*p[i][k]) ){
						dp[i][j] = s + c*p[i][k];
						price[i][j] = p[i][k];
					}
					else if (dp[i][j] == (s + c*p[i][k]) && price[i][j] > p[i][k]){
						price[i][j] = p[i][k];
					}
				}
			}
		}
		printf("%d\n%d\n",dp[W-1][N],price[W-1][N]);
	}
	return 0;
}

