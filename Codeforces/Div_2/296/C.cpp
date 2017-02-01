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

const int MAXN = 200005;

long long res[MAXN];
bool type[MAXN];
int val[MAXN];
set<int> X;
set<int> Y;

int get_max( set<int> &V ){
	int len = 0;
	set<int>::iterator act = V.begin();
	set<int>::iterator prev = act++;
	for ( ; act != V.end(); act++ ){
		len = max( len , *act - *prev );
		prev = act;
	}
	return len;
}

int rem( set<int> &V, int v ){
	set<int>::iterator it = V.find( v );
	set<int>::iterator tmp = it;
	tmp--;
	V.erase( it );
	it = tmp;
	tmp++;
	return *tmp - *it;
}

int main(){
	char ch;
	int v;
	int W, H, N;

	scanf("%d %d %d", &W, &H, &N);	
	X.insert( 0 );
	X.insert( W );
	Y.insert( 0 );
	Y.insert( H );
	for ( int i=0; i<N; ++i ){
		scanf(" %c %d", &ch, &v);
		if ( ch == 'H' ){
			Y.insert( v );
			type[i] = true;
			val[i] = v;
		}
		else {
			X.insert( v );
			type[i] = false;
			val[i] = v;
		}
	}
	int maxX = get_max( X );
	int maxY = get_max( Y );
	
	res[N-1] = 1LL*maxX*maxY;
	for ( int i=N-1; i > 0; i-- ){
		if ( type[ i ] ){
			maxY = max( maxY , rem( Y, val[i] ) );
			res[i-1] = max( res[i] , 1LL*maxX*maxY );
		}
		else {
			maxX = max( maxX, rem( X, val[i] ) );
			res[i-1] = max( res[i] , 1LL*maxX*maxY ); 
		}
	}
	for ( int i=0; i < N; ++i ) printf("%I64d\n", res[i]);
	return 0;
}

