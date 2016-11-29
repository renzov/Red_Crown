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
#include <cassert>

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

const int MAXN = 290177;

int d[MAXN]={0};

void sieve(){
	for ( int i=2; i <= MAXN; i+=2 ) d[i] = 2;
	for ( int i=3; i <= MAXN; i += 2 ){
		if ( !d[i] ){
			d[i] = i;
			if ( i < 540 ){ // i*i <= MAXN
				for ( int j=i*i; j <= MAXN; j += (i<<1) )
					d[j] = i;
			}
		}
	}
}


int main(){
	int lucky[1005];
	int cnt, tmp;
	int f, k;
	sieve();
	// Precompute the lucky numbers
	k = 0;
	for ( int i=30; k < 1000 && i <= MAXN; ++i ){
		// Factorize the number
		cnt = 0;
		tmp = i;
		if ( d[tmp] > 0 ){
			while ( tmp > 1 ){
				cnt++;
				f = d[tmp];
				while ( tmp%f == 0 ) tmp /= f;
			}
			if ( cnt >= 3 ) lucky[k++] = i;
		}
	}
	int runs, N;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &N);
		printf("%d\n", lucky[N-1]);
	}
	return 0;
}

