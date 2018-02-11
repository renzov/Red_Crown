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
typedef pair< long long, int > pii;

int main(){
	int N, T;
	
	priority_queue<pii> q;
	scanf("%d", &N);
	for ( int i=1; i <= N; ++i ){
		scanf("%d", &T);
		long long val = 1;
		int t;
		while ( T-- ){
			scanf("%d", &t);
			val *= t;
		}
		q.push( pii( val, i ) );
	}
	for ( int i=0; i < 3; ++i ){
		printf("%d\n", q.top().second);
		q.pop();
	}
	return 0;
}

