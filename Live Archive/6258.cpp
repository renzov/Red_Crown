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

const int MAXN = 200005;
int N;

pii a[MAXN];
int L[MAXN];
int R[MAXN];

bool solve( int l, int r ){
	if ( l > r ) return true;
	for ( int i=l, j=r; i <= j ; i++, j-- ){
		if ( L[i] < l && R[i] > r ){
			return solve( l , i - 1  ) && solve( i + 1, r );
		}
		else if ( L[j] < l && R[j] > r ){
			return solve( l, j - 1 ) && solve( j + 1, r );
		}
	}
	return false;
}

int main(){
	int runs;
	int last;
	int act, pre;

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &N);
		for ( int i=0; i < N; ++i ){
			scanf("%d", &a[i].first);
			a[i].second = i;
		}
		sort( a, a + N );
		// find L and R
		last = -1;
		// Left array
		for ( int i=0; i < N; ++i ){
			act = a[i].second;	// index
			if ( a[i].first != last ){ // first element of that value
				L[ act ] = -INT_MAX; // -oo
				last = a[i].first;
			}
			else {
				L[ act ] = pre;
			}
			pre = act;
		}
		// Right array
		last = -1;
		for ( int i=N-1; i >= 0; --i ){
			act = a[i].second;
			if ( a[i].first != last ){
				R[ act ] = INT_MAX; // +oo
				last = a[i].first;
			}
			else {
				R[ act ] = pre;
			}
			pre = act;
		}
		if ( solve( 0, N-1 ) ) puts("non-boring");
		else puts("boring");
	}
	return 0;
}

