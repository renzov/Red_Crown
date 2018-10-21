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
#define X first
#define Y second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;
const int MAXN = 100005;
pii P[MAXN];

int main(){
	int N;
	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d %d", &P[i].X, &P[i].Y);
	}
	sort( P, P + N );
	int lastY = 0;
	int y, x;
	int res = 0;
	for ( int i=N - 1; i >= 0; ){
		x = P[i].X;
		y = P[i].Y;
		while ( i >= 0 && P[i].X == x ){
			if ( lastY <= P[i].Y ) res++;
			i--;
		}
		lastY = max( lastY , y );
	}
	printf("%d", res);
	return 0;
}

