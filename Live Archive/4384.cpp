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

bool check( int L, const int &x, const int &y ){
	while ( (L - x) >= 0 ){
		L -= x;
		if ( L % y == 0 ) return true;
	}
	return false;
}

int main(){
	int a,b,c,d;
	int runs;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d %d %d", &a, &b, &c, &d);
		if ( c%a == 0 && d%b == 0 ) puts("YES");
		else if ( c%b == 0 && d%a == 0 ) puts("YES");
		else if ( c%a == 0 && c%b == 0 && check(d,a,b) ) puts("YES");
		else if ( d%a == 0 && d%b == 0 && check(c,a,b) ) puts("YES");
		else puts("NO");
	}
	return 0;
}

