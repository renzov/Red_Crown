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

vector<int> G[ 55 ];
bool pos[55][25];

int main(){

	int u,v;
	int n,m,k;

	while ( scanf("%d %d %d",&n,&m,&k) && ( n + m + k ) ){
		for ( int i=0; i < n; ++i ){
			G[i].clear();
			for ( int j=1; j <= 20; ++j )
				pos[i][j] = false;
		}
		for ( int i=0; i < m; ++i ){
			scanf("%d %d",&u,&v);
			G[u].push_back(v);
		}
		
		pos[0][1] = true;
		bool found = false;
		for ( int j=1; j < 20; ++j ){
			
			if ( j >= k && pos[n-1][j] ){
				printf("%d\n",j);
				found = true;
				break;
			}

			for ( u=0; u < n; ++u ){
				if ( pos[u][j] ){
					for ( int i=0; i < G[u].size(); ++i ){
						v = G[u][i];
						pos[v][j+1] = true;
					}
				}
			}
		}
		if ( !found ){
			if ( pos[n-1][20] ) printf("20\n");
			else puts("LOSER");
		}
	}
	return 0;
}

