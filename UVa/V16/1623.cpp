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

const int MAXN = 1000005;

bool in[ MAXN ];
int rain[ MAXN ];
int last[ MAXN ];
int nxt[ MAXN ];
int res[ MAXN ];
set< pii >::iterator it;

int main(){
	int N,M;
	int runs;
	int i;
	int size,lake;
	bool ok;

	scanf("%d",&runs);
	while ( runs-- ){
		scanf("%d %d",&N,&M);		
		fill( nxt + 1 , nxt + M + 1 , 0 );
		set< pii > E;		
		for ( i = 1; i <= N; ++i ){
		 	last[i] = 0;
			in[i] = true;
		}
		for ( i = 1; i <= M; ++i ){
			scanf("%d", rain + i );
			if ( rain[i] ){
				if ( last[ rain[i] ] ){
					nxt[ last[ rain[i] ] ] = i;
				}
				else {
					E.insert( mp( i , rain[i] ) );
				}
				last[ rain[i] ] = i;
			}
		}
		
		ok = true;
		size = 0;
		for ( i = 1; i <= M && ok; ++i ){
			if ( rain[i] ){
				if ( in[ rain[i] ] ) ok = false;
				else {
					in[ rain[i] ] = true;
					if ( nxt[i] ) E.insert( mp( nxt[i] , rain[i] ) );
				}
			}
			else {
				if ( !E.empty() ){
					it = E.begin();
					lake = it->second;
					res[ size++ ] = lake;
					E.erase( it );
					in[ lake ] = false;
				}
				else {
					res[size++] = 0;
				}
			}
		}

		if( !ok ) puts("NO");
		else {
			puts("YES");
			if ( size ){
				printf("%d", res[0]);
				for ( i=1; i < size; ++i ) printf(" %d", res[i]);
				puts("");
			}
		}
	}
	return 0;
}

