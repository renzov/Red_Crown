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

const int MAXN = 1000000000;
int powers[100000];
int M;

int main(){
	int M = 0;
	for ( long long i=1; i*i <= MAXN; ++i ){
		powers[M++] = (int)(i*i);
	}
	int N;
	int runs;
	int idx;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &N);
		idx = lower_bound( powers, powers + M,  N ) - powers;
		if ( idx <  M && powers[idx] == N ){
			printf("0 %d\n", idx + 1);
			continue;
		}
		long long a, b;
		long long x, y;
		long long resX = INT_MAX, resY = INT_MAX;
		for ( a = 1; a*a < N; ++a ){
			if ( N % a == 0 ){
				b = N / a;
				if ( ( (a ^ b) & 1 ) == 0 ){
					x = ( a + b ) >> 1;
					y = ( b - a ) >> 1;
					if ( resY > y || (resY == y && resX > x) ){
						resY = y, resX = x;
					}
				}
			}
		}
		if ( resY == INT_MAX ) puts("IMPOSSIBLE");
		else printf("%lld %lld\n", resY, resX);
	}
	return 0;
}

