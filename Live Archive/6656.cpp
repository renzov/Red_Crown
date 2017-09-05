#include <cstdio>
#include <algorithm>
#include <set>
#include <cctype>
#include <string>
#include <vector>

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
typedef pair< int, int > pii;
typedef pair< pii, pii > event;

int N, M;
int e;

const int MAXM = 100005;
int res[MAXM];
event E[ 5*MAXM ];
int left[MAXM];
int right[MAXM];

int main(){
	int cases = 0;
	int runs;
	int l, r, m;

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d", &N, &M);
		e = 0; // Number of events to process
		// Read the info of the intervals
		for ( int i=0; i < N; ++i ){
			scanf("%d %d", &l, &r);
			left[i] = l; 
			right[i] = r;
			m = ( l + r ) >> 1;	// Mid point of the interval
			E[ e++ ] = event( pii( l , 0 ) , pii( 0 , i ) ); // Left interval insert
			E[ e++ ] = event( pii( m, 2 ) , pii( 0 , i ) );  // Left interval delete
			E[ e++ ] = event( pii( m + 1 , 0 ) , pii( 1 , i ) ); // Right interval insert  
			E[ e++ ] = event( pii( r , 2 ) , pii( 1 , i ) ); // Right interval delete 
		}
		// Read the queries
		for ( int i=0; i < M; ++i ){
			scanf("%d", &l);
			E[e++] = event( pii( l, 1 ) , pii( -1 , i ) );
		}
		sort( E, E + e );
		// Do sweep line
		set< pii > L; // Set of "active" lett intervals 
		set< pii > R; // Set of "active" right interval
		int x;
		int idx;
		for ( int i=0; i < e; ){
			x = E[i].first.first;
			do {
				idx = E[i].second.second;				
				switch ( E[i].first.second ){ 
					case 0 : // Insertion
							if ( E[i].second.first == 0 ){
								L.insert( pii( left[idx] , idx ) );
							}
							else {
								R.insert( pii( right[idx] , idx ) );
							}
							break;
					case 1 : // Query
							res[ idx ] = 0;
							if ( !L.empty() ){
								res[ idx ] = max( res[idx] , x - L.begin()->first ); 
							}
							if ( !R.empty() ){
								res[idx] = max( res[idx] , R.rbegin()->first - x );
							}
							break;
					case 2 : // Deletion
							if ( E[i].second.first == 0 ){
								L.erase( pii( left[idx], idx ) );
							}
							else {
								R.erase( pii( right[idx], idx ) );
							}
							break;
				}
				i++;
			}
			while ( i < e && x == E[i].first.first );
		}
		printf("Case %d:\n", ++cases);
		for ( int i=0; i < M; ++i ) printf("%d\n", res[i]);

	}
	return 0;
}

