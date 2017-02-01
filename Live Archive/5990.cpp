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

const int MOD = 1000000007;
const int MAXN = 100005;
int a[MAXN];
int pot[MAXN];

int main(){
	int runs;
	int N;
	int m, M;
	int cntmin, cntmax;
	long long res1, res2;
	long long tmp;
	int lastmax, lastmin;
	// precal 2 ^ i % MOD 
	pot[0] = 1;
	for ( int i=1; i <= 100000; ++i ){
		pot[i] = pot[i-1] * 2;
		pot[i] %= MOD;
	}

	scanf("%d", &runs);
	while ( runs-- ){
		M = -INT_MAX;
		m = INT_MAX;
		scanf("%d", &N);
		for ( int i=0; i < N; ++i ){
			scanf("%d", a+i );
			if ( a[i] < m ) m = a[i], cntmin = 1;
			else if ( a[i] == m ) cntmin++;
			if ( a[i] > M ) M = a[i], cntmax = 1;
			else if ( a[i] == M ) cntmax++;
		}
		if ( m == M ){
			res2 = ( pot[N] + (MOD - 1) ) % MOD;
			res1 = (long long)N * (N + 1);
			res1 >>= 1;
			res1 %= MOD;
		}
		else {
			// First count the subsequences
			res2 = (pot[cntmin] + (MOD - 1) )% MOD;
			tmp = (pot[cntmax] + (MOD - 1) )% MOD;
			res2 *= tmp;
			res2 %= MOD;
			res2 *= pot[N - cntmin - cntmax];
			res2 %= MOD;
			// Now, count the substrings
			lastmax = -1;
			lastmin = -1;
			res1 = 0;
			for ( int i=0; i < N; ++i ){
				if ( a[i] == m ){
					res1 += ( lastmax + 1 );
					res1 %= MOD;
					lastmin = i;
				}
				else if ( a[i] == M ){
					res1 += ( lastmin + 1 );
					res1 %= MOD;
					lastmax = i;
				}
				else {
					res1 += ( min(lastmin, lastmax) + 1 );
					res1 %= MOD;
				}
			}
		}
		printf("%lld %lld\n", res1, res2 );
	}
	return 0;
}

