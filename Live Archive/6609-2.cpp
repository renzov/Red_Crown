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

const int MAXN = 500005;

int a[MAXN];
int S[MAXN];
int sz;
long long V[MAXN];
long long sum;
int N;
long long X;

inline long long f( const long long &v ){ return sum - v; }

int main(){
	int runs;	
	int res;
	int best;
	int l, r, m;
	int base;
	int last_pop;

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %lld", &N, &X);
		for ( int i=0; i < N; ++i ) scanf("%d", a+i);		
		long long prevSum = 0;
		sz = 0; // empty stack
		base = 0;
		res = INT_MAX;
		for ( int i=0; i < N; ++i ){
			sum = prevSum + a[i];
			// Maintain the invariant 
			while ( sz > base && f(V[sz - 1]) <= a[i] ) sz--;  
			S[sz] = i, V[sz] = prevSum;
			sz++;
			last_pop = -1;
			while ( base < sz && f( V[base] ) >= X ){ 
				last_pop = S[base];
				base++;	
			}
			if ( last_pop != -1 ) res = min( res , i - last_pop + 1 );
			prevSum = sum;
		}
		if ( res < INT_MAX ) printf("%d\n", res);
		else puts("-1");
	}
	return 0;
}

