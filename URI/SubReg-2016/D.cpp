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

const int MAXSQRT = 31622;

int main(){
	int A, B, C, D;
	int f, k1, k2;
	int N;
	int res = INT_MAX;
	scanf("%d %d %d %d", &A, &B, &C, &D);
	if ( C % A ){ puts("-1"); return 0; }
	f = C / A;
	for ( int i=1; i <= MAXSQRT && i*i <= f; ++i ){
		if ( f % i ) continue;
		k1 = i, k2 = f / i;
		if ( (C % k1) || (C % k2) ) continue;
		N = C / k1;
		if ( N % B && D % N ) res = min( res, N );
		N = C / k2;
		if ( N % B && D % N ) res = min( res, N );
	}
	if ( res == INT_MAX ) puts("-1");
	else printf("%d\n", res);
	return 0;
}
