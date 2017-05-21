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

const int MAXN = 1000001;
int d[MAXN] = {0};

void sieve(){
	for ( int i=2; i <= MAXN; i+=2 ) d[i] = 2;

	for ( int i=3; i <= 1000; i += 2 ){
		if ( !d[i] ){
			d[i] = i;
			for ( int j=i*i; j < MAXN; j += (i<<1) )
				d[j] = i;
		}
	}
	for ( int i=3; i < MAXN; i+=2 )
		if ( !d[i] ) d[i] = i;
}


int main(){
	sieve();

	int runs;
	int f, cnt;
	int res, N;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &N);
		res = 1;
		while ( N > 1 ){
			f = d[N];
			cnt = 0;
			while ( N % f == 0 ) N /= f, cnt++;
			if ( cnt > res ) res = cnt;
		}
		printf("%d\n", res);
	}
	return 0;
}
