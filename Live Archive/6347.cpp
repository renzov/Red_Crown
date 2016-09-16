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

int main(){
	int N, K;
	int runs;
	int res, cnt;
	char c, last;
	int maxf;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d", &N, &K);
		last = '\0';
		maxf = 0;
		cnt = 0;
		res = 0;
		for ( int i=0; i < N; ++i ){
			scanf(" %c", &c);
			if ( c == last ) cnt++;
			else {
				if ( maxf < cnt ) maxf = cnt;
				res += (( cnt + K - 1) / K );	
				cnt = 1;
				last = c;
			}
		}
		if ( maxf < cnt ) maxf = cnt;
		res += ((cnt + K - 1) / K);
		if ( maxf >= K )
			printf("%d\n", res);
		else 
			puts("-1");
	}
	return 0;
}

