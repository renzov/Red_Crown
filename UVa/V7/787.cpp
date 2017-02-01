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

int a[200];
long long p[200][200];
int n;

int main(){
	long long m;

	while ( scanf("%d",a) != EOF ){
		
		if (a[0] == -999999 ){
			puts("0");
			continue;
		}
		
		n = 1;
		m = -INT_MAX;
	
		while ( scanf("%d",a+n) && a[n] != -999999 )
			n++;
		
		for ( int i=0; i < n; ++i ){
			p[i][i] = a[i];
			m = max( m , p[i][i] );
			for ( int j=i+1; j < n ; ++j ){
				p[i][j] = p[i][j-1] * a[j];
				m = max( p[i][j] , m );
			}
		}
		
		printf("%lld\n",m);
	
	}
	return 0;
}

