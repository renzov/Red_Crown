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
#include <climits>

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
const int INF = INT_MAX;
int K,L;
char key[100];
char letter[100];
long long sum[100] = {0};
int F[100];

long long dp[100][100];
int last[100][100];

/*  
	dp[i][j] = min average cost of alphabet 1...i with at most j keys. 
*/

int main(){
	int runs;
	long long S;
	int cases = 0;
	scanf("%d",&runs);

	while ( runs-- ){
		cases++;
		scanf("%d %d",&K,&L);
		scanf("%s",key);
		scanf("%s",letter);
		for ( int i=1; i <= L; ++i ){
			scanf("%d",F+i);
			sum[i] = sum[i - 1] + F[i];
		}
		
		for ( int i=1; i <= L ; ++i ){
			dp[i][1] = dp[i - 1][1] + i*F[i];
		}

		for ( int j=2 ; j <= K ; j++ ){
		
			dp[1][j] = dp[1][j-1]; //Just one letter
			last[1][j] = -1;

			for ( int i=2; i <= L ; ++i ){
			
				dp[i][j] = INF;
				
				S = 0;

				for ( int k=i-1 ; k >= 1 ; --k ){
					S += (sum[ i ] - sum[ k ]);
					if ( dp[k][j-1] < INF && 
						(dp[k][j-1] + S) <= dp[i][j]
					){
						dp[i][j] = dp[k][j-1] + S;
						last[i][j] = k;
					}
				}
			
				if ( dp[i][j-1] <= dp[i][j] ){
					dp[i][j] = dp[i][j-1];
					last[i][j] = -1; 
				}

			}
		}

		int x = L,y = K;
		vector< pii > sol;
		do {
			if ( y == 1 ){
				sol.push_back( make_pair( 1 , x ) );
			}
			else if ( last[x][y] != -1 ){
				sol.push_back( make_pair( last[x][y] + 1 , x ) );
				x = last[x][y];
			}
			y--;
		}
		while ( y > 0 );
		
		printf("Keypad #%d:\n",cases);
		
		vector<pii>::reverse_iterator it;
		int l,r;
		int p = 0;
		for ( it = sol.rbegin(); it != sol.rend() ; ++it, ++p ){
			l = it->first;	
			r = it->second;
			printf("%c: ",key[p]);
			for ( int i=l; i <= r ; ++i )
				printf("%c",letter[ i - 1 ]);
			puts("");
		}
		puts("");
	}
	return 0;
}

