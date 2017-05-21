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

const int MAXN = 10000;
const int SQRT = 100;

bool nop[MAXN + 2];
int d[MAXN + 2] = {0};
int L[MAXN];

void sieve(){
	d[2] = 2;
	for ( int i=4; i <= MAXN; i += 2 )
		d[i] = 2, nop[i] = true; 

	for ( int i=3; i < SQRT; i += 2 ){
		if ( !nop[i] ){
			d[i] = i;
			for( int j = i*i; j <= MAXN; j += (i<<1) ){
				nop[j] = true, d[j] = i;
			}
		}
	}
	for ( int i=3; i <= MAXN; i+= 2 ){
		if ( !d[i] ) d[i] = i; 
	}
}

int main(){
	
	int N = 0;
	int val;
	int t, cnt, f;

	sieve();
	// precalc a list of acc numbers 
	for ( int i=2; i <= MAXN; ++i ){
		val = 1;
		// factor i
		t = i;
		while ( t > 1 ){
			f = d[t];
			cnt = 0;
			while ( t % f == 0 ) cnt++, t /= f;
			val *= ( cnt + 1 ); 
		}
		if ( val <= MAXN && !nop[val] ) L[N++] = i;
	}
	
	int runs;
	int a, b;
	int idx;
	bool first;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d", &a, &b);
		idx = lower_bound( L, L + N, a ) - L;
		first = false;
		while ( idx < N && L[idx] <= b ){
			if ( !first ) first = true;
			else putchar(' ');
			printf("%d", L[idx]);
			idx++;
		}
		if (!first) puts("-1");
		else puts("");
	}
	return 0;
}

