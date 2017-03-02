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
	scanf("%d", &runs);
	int res;
	int best;
	int l, r, m;
	while ( runs-- ){
		scanf("%d %lld", &N, &X);
		for ( int i=0; i < N; ++i ) scanf("%d", a+i);
		
		long long prevSum = 0;
		sz = 0; // empty stack
		res = INT_MAX;
		for ( int i=0; i < N; ++i ){
			sum = prevSum + a[i];
			// Maintain the invariant 
			while ( sz > 0 && f(V[sz - 1]) <= a[i] ) sz--;  
			S[sz] = i, V[sz] = prevSum;
			sz++;
			// binary search for the answer
			if ( f(V[0]) >= X ){ // if there is a solution 
				if ( f( V[sz-1] ) >= X ){
					best = S[sz-1];
				}
				else {
					r = sz - 1; // not a solution
					l = 0; // a solution
					while ( r - l > 1 ){
						m = ( l + r ) >> 1;
						if ( f( V[m] ) >= X ) l = m;
						else r = m;
					}
					best = S[l];
				}
				res = min( res, i - best + 1 );
			}
			prevSum = sum;
		}
		if ( res < INT_MAX ) printf("%d\n", res);
		else puts("-1");
	}
	return 0;
}

