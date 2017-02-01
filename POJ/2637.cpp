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
#include <cassert>
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

const int MAXN = 50005;

int Y[MAXN];
int V[MAXN];
int segtree[4 * MAXN];

void build( int N , int L , int R ){
	if ( L==R ){
		segtree[N] = V[L];
		return;
	}
	int M = (L+R)>>1;
	build( N << 1 , L , M );
	build( (N<<1)|1 , M + 1 , R );
	segtree[N] = max( segtree[N<<1] , segtree[(N<<1)|1] );
}

int query( int N , int L , int R , int l , int r ){
	if ( l > r ) return -1;
	if ( l <= L && r >= R ) return segtree[N];
	int M = (L+R)>>1;
	if ( r <= M ) return query( N << 1 , L , M , l , r );
	if ( l > M ) return query( (N << 1) | 1 , M + 1 , R , l , r );
	return max( query(N<<1, L , M , l , M) , query((N<<1)|1,M+1,R,M+1,r) );
}

int main(){
	int n;
	int q;
	int a,b;
	int l,r;
	int val;
	int m;
	int cases = 0;
	while ( scanf("%d",&n) && n ){
		cases++;
		for ( int i=1; i <= n; ++i ){
			scanf("%d %d",Y + i,V + i);
		}
		
		build( 1  , 1 , n );
		scanf("%d",&q);
		
		if (cases > 1) puts("");

		while (q--){
			scanf("%d %d",&a,&b);
			r = lower_bound( Y + 1 , Y + n + 1 , b ) - Y;
			l = lower_bound( Y + 1 , Y + n + 1, a ) - Y;
			
			if (Y[r] > b) r--;
			// Y[r] <= b && Y[l] >= a
			if ( (b-a) == (r - l) ){
				// Y[r] == b && Y[l] == a 
				m = query( 1 , 1 ,  n , l + 1 , r - 1 );
				if ( V[r] <= V[l] && m < V[r] ) puts("true");
				else puts("false");
			}
			else {
				if ( Y[r] < b && Y[l] > a ) puts("maybe"); //You can put "infinite" value to years a and b, to make it true
				else {
					int L = ( Y[l] == a )? (l+1):l;
					int R = ( Y[r] == b )? (r-1):r;
					m = query( 1 , 1 , n , L , R );
					if ( Y[l] == a && Y[r] == b ){
						if ( V[l] >= V[r] && m < V[r] ) puts("maybe");
						else puts("false");
					}
					else if ( Y[l] == a ){
						if (V[l] > m) puts("maybe");
						else puts("false");
					}
					else { // Y[r] == b 
						if (V[r] > m) puts("maybe");
						else puts("false");
					}
				}
			}
		}
	}	

	return 0;
}

