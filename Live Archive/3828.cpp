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

int a[300];
int b[300];

void transform( int s ){
	int tmp;
	for ( int i=0; i < s; ++i ){
		tmp = a[i] + a[i + s];
		b[2*i] = tmp >> 1;
		b[2*i + 1] = b[2*i] - a[i + s];
	}
	for ( int i=0; i < (s << 1); ++i )
		a[i] = b[i];
}

int main(){

	int n;

	while ( scanf("%d",&n) && n ){
		for ( int i=0; i < n; ++i ){
			scanf("%d",a+i);
		}
		int size = 1;
		while ( size < n ){
			transform( size );
			size *= 2;
		}
		printf("%d",a[0]);
		for (int i=1; i<n ;i++)
			printf(" %d",a[i]);
		puts("");
	}
	return 0;
}

