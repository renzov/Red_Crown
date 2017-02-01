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

int main(){
	int N, Q;
	int X, m, M;

	scanf("%d %d", &N, &Q);
	m = INT_MAX;
	M = -1;
	for ( int i=0; i < N; ++i ){
		scanf("%d", &X);
		m = min( X , m );
		M = max( X , M );
	}
	while ( Q-- ){
		scanf("%d", &X);
		if ( m <= X && X <= M ) puts("Yes");
		else puts("No");
	}
	return 0;
}

