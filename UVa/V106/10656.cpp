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

int a[1005];

int main(){
	int n;
	int m;
	while ( scanf("%d",&n) && n ){
		m = 0;
		for ( int i=0; i < n; ++i ){
			scanf("%d",a+m);
			if (a[m] != 0) m++;
		}
		if ( m == 0 ) puts("0");
		else {
			for (int i=0; i < m ; ++i){
				if ( i ) putchar(' ');
				printf("%d",a[i]);
			}
			puts("");
		}
	}

	return 0;
}

