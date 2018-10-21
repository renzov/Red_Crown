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

long long dp[65][2];
int stamp[65][2];
long long N;
long long X;
int t;

long long solve( const int &pos, const int &less ){
	if ( pos < 0 ) return 1;
	if ( stamp[pos][less] == t ) return dp[pos][less];
	stamp[pos][less] = t;
	long long &res = dp[pos][less] = 0;
	int bitN = (N >> pos) & 1;
	int bitX = (X >> pos) & 1;
	if ( bitX == 1 ){ // We have to put a 1 in that position
		if ( less ) res += solve( pos - 1, less ); 
		else if ( bitN == 1 ) res += solve( pos - 1, less );
	}
	else { // you can put 0 or 1
		if ( less ){
			res += 2*solve( pos - 1 , less );
		}
		else { // less == 0
			if ( bitN == 1 ){
				res += solve( pos - 1, less );
				res += solve( pos - 1, 1 );
			}
			else {
				res += solve( pos - 1, less );
			}
		}
	}
	return res;
}

int main(){
	int Q;
	long long A, B;
	long long resA;
	long long resB;
	t = 0;
	scanf("%d", &Q);
	for ( int i=0; i < Q; ++i ){
		scanf("%lld %lld %lld", &A, &B, &X);
		N = A - 1;
		t++;
		resA = solve( 63 ,  0 );
		N = B;
		t++;
		resB = solve( 63 , 0 );
		printf("%lld\n", resB - resA );
	}
	return 0;
}

