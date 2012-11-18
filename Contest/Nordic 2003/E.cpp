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
const int limit = 1000000000;

int main(){
	int runs;
	int64 MCM;
	bool overf;
	int x;
	int n;
	int g;
	scanf("%d",&runs);
	while ( runs-- ){
		scanf("%d",&n);
		overf = false;
		MCM = 1;
		for ( int i=0; i < n; ++i ){
			scanf("%d",&x);
			if ( !overf ){
				g = __gcd((int)MCM,x);
				MCM /= g; MCM *= x;
				if ( MCM > limit ) overf = true;
			}
		}
		if (overf) puts("More than a billion.");
		else printf("%d\n",(int)MCM);
	}
	return 0;
}

