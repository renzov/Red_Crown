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

const int MAXN = 30000000;
int S[MAXN] = {0};

int main(){
	// Precalc all the answers
	for ( int i=1; i <= MAXN; i++ ) 
		for ( int j=(i<<1); j <= MAXN; j += i )
			if ( (j ^ (j-i)) == i ) S[j]++;

	for ( int i=2; i <= MAXN; ++i ) S[i] += S[i-1];
	// Process input 
	int runs;
	int cases = 0;
	int N;

	scanf("%d",&runs);
	while ( runs-- ){
		scanf("%d", &N);
		printf("Case %d: %d\n", ++cases, S[N]);
	}
	return 0;
}

