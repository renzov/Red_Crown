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

int dx[] = {1,1,0,-1,-1,-1,0,1};
int dy[] = {0,1,1,1,0,-1,-1,-1};

inline long long area2( const long long &x1, const long long &y1, const long long &x2, const long long &y2 ){
	return x1 * y2 - x2 * y1;
}

int read_line(){
	char c;
	long long x = 0,y = 0;
	long long nx,ny;
	int k;
	long long B = 1;
	long long A2 = 0;
	long long I;

	while ( (c=getchar()) != '\n' ){
		if ( c == EOF ) return 0;
		k = c - '0';
		nx = x + dx[k];
		ny = y + dy[k];
		B++;
		A2 += area2(x,y,nx,ny);
		x = nx, y = ny;
	}
	I = (A2 - B + 1) / 2;
	printf("%lld\n",I + B);
	return 1;
}

int main(){

	while ( read_line() );
	
	return 0;
}

