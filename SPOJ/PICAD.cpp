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

const int MAXN = 5005;

pair<int,int> evt[2*MAXN];

int main(){
	int N;
	int x,y,L,R;

	while ( scanf("%d %d",&L,&R) != EOF ){
		scanf("%d",&N);
		L <<= 1;
		R <<= 1;
		for ( int i=1; i <= N; ++i ){
			scanf("%d %d",&x,&y);
			evt[ 2*i ] = make_pair( 2*x - 1 , 1 );
			evt[ 2*i + 1 ] = make_pair( 2*y + 1 , -1 );
		}
		
		evt[0] = make_pair( L , 0 );
		evt[1] = make_pair( R , 0 );
		N++;

		sort( evt , evt + 2*N );
		int mini = N;
		int maxi = 0;
		int cnt = 0; 

		for ( int i=0; i < 2*N; ++i){
			if ( L <= evt[i].first && evt[i].first <= R ){
				maxi = max( maxi , cnt );
				mini = min( mini , cnt );
			}
			cnt += evt[i].second;
		}
		printf("%d %d\n",mini,maxi);
	}
	return 0;
}
