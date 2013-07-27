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

pii a[1200];

int main(){
	int runs = 0;
	int n;
	
	while (scanf("%d",&n) && n){
		runs++;
		for ( int i=0; i < n; ++i )
			scanf("%d %d",&a[i].second,&a[i].first);
		sort(a , a + n);
		
		int M = -INT_MAX;
		int b = 0;
		for ( int i=n-1; i >= 0; --i ){
			M = max( a[i].first + a[i].second + b , M );
			b += a[i].second;
		}
		printf("Case %d: %d\n",runs,M);
	}
	return 0;
}

