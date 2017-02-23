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

int R[20];

int main(){
	int runs, n;
	int sum;
	int x, y;
	int d;

	for ( int i=20, j=1; i <= 200; i += 20, j++ ) R[j] = i*i;

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &n);
		sum = 0;
		for ( int i=0; i < n; ++i ){
			scanf("%d %d", &x, &y);
			d = x*x + y*y;
			for ( int j=1; j <= 10; ++j ){
				if ( R[j] >= d ){
					sum += (11 - j);
					break;
				}
			}
		}
		printf("%d\n", sum);
	}
	return 0;
}

