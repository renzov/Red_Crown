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

const int MAXN = 100005;

char G[MAXN];

int main(){
	int N, S, J, D;
	int A, B;
	int rA, rB;
	while ( scanf("%d %d %d %d", &N, &S, &J, &D) != EOF ){
		scanf("%s", G);
		A = B = rA = rB = 0;
		for ( int i=0; i < N; ++i ){
			if ( G[i] == 'A' ) A++;
			else B++;

			if ( A >= J && (A - B) >= D ){
				rA++;
				A = B = 0;
			}
			else if ( B >= J && ( B - A ) >= D ){
				rB++;
				A = B = 0;
			}
		}
		printf("%d %d\n", rA, rB);
	}
	return 0;
}

