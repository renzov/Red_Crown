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
int M;

int F( int n , int k ){
	if ( k == 0 ) return 1;
	if ( k == 1 ) return n % M;

	if ( k & 1 ) return (n * F( n , k - 1 )) % M;
	int v = F( n , k >> 1 );
	return (v * v) % M;
}

int main(){
	int N,K,S,X;
	int runs;
	int cases = 0;

	scanf("%d",&runs);
	while ( runs-- ){
		cases++;
		scanf("%d %d %d",&N,&K,&M);
		S = 0;
		for ( int i=0; i < N; ++i ){
			scanf("%d",&X); 
			X %= M;
			S += X;
			S %= M;
		}
		printf("%d\n",S);
		printf("%d\n",F(N,K));
		printf("Case %d: %d\n", cases , ( S * F(N,K) ) % M );
	}
	return 0;
}

