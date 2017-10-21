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

const int MAXN = 20005;
int H[MAXN];

int main(){
	int res;
	int runs;
	int N, K;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d", &N, &K);
		for ( int i=0; i < N; ++i ) scanf("%d", H + i);
		sort( H , H + N );
		res = INT_MAX;
		for ( int i=0; (i + K) <=  N; ++i )
			res = min( res , H[i+K - 1] - H[i] );
		printf("%d\n", res);
	}
	return 0;
}

