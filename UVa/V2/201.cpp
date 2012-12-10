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

bool con[10][10][10][10];

int main(){
	char t;
	int i,j;
	int n,m;
	int runs = 0;
	while ( scanf("%d",&n) != EOF ){
		runs++;
		scanf("%d",&m);
		memset(con,false,sizeof(con));
		for ( int k=0; k < m; ++k ){
			scanf(" %c %d %d",&t,&i,&j);
			j--,i--;
			if ( t == 'H' ){
				con[i][j][i][j+1] = con[i][j+1][i][j] = true;
			}
			else {
				con[j][i][j+1][i] = con[j+1][i][j][i] = true;	
			}
		}

		for ( i=0; i < n; ++i ){
			for ( j=0; j < n; ++j ){
				int k = 0;
				while ( (j + k + 1) < n ){
					if ( con[i][j+k][i][j+k+1] ){
						con[i][j][i][j+k+1] = true;
						con[i][j+k+1][i][j] = true;
						k++;
					}
					else { 
						break; 
					}
				}
				k = 0;
				while ( (i + k + 1) < n ){
					if ( con[i+k][j][i+k+1][j] ){
						con[i][j][i+k+1][j] = true;
						con[i+k+1][j][i][j] = true;
						k++;
					}
					else { 
						break; 
					}
				}
			}
		}

		int count[ 15 ] = {0};

		for (int k=1; k < n ; ++k)
			for ( int i=0;  i < n; ++i ){
				for ( int j=0; j < n; ++j ){
					if ( ((i + k) < n) && ((j + k) < n) )
						count[k] += ( con[i][j][i][j + k] && con[i][j][i+k][j] && con[i+k][j][i+k][j+k] && con[i][j+k][i+k][j+k] );
				}
			}
		
		if ( runs > 1 ){
			printf("\n**********************************\n\n");
		}
		printf("Problem #%d\n\n",runs);
		bool zero = true;
		for ( int k=1; k < n ; ++k ){
			if ( count[k] ){
				zero = false;
				printf("%d square (s) of size %d\n",count[k],k);
			}
		}
		if ( zero ) puts("No completed squares can be found.");
	}
	
	return 0;
}

