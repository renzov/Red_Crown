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

const int MAXN = 1 << 20;
const int SQRT = 1 << 10;
int fact[MAXN] = {0};
int d[MAXN + 2] = {0};

void sieve(){
	for ( int i=2; i <= MAXN; i += 2 ) d[i] = 2;
	for ( int i=3; i < SQRT; i += 2 ){
		if ( !d[i] ){
			d[i] = i;
			for ( int j=i*i; j <= MAXN; j += (i<<1) )
				d[j] = i;
		}
	}
	for ( int i=3; i < MAXN; i += 2 ) 
		if ( !d[i] ) d[i] = i;
}

int main(){
	int res1;
	long long res2;
	int N;
	int t, f;
	map<int,int> pre[21];


	sieve();
	// Precalc the factorization of X! for X = 2, 3, ..., 20
	for ( int i=2; i <= 20; ++i ){
		for ( int j=2; j <= i; ++j ){
			t = j;
			while ( t > 1 ){
				f = d[t];
				t /= f;
				pre[i][f]++;
			}
		}
	}

	while ( scanf("%d", &N) != EOF ){
		map<int,int> C;
		map<int,int> T;	
		// factor N
		res1 = 0;
		while ( N > 1 ){
			f = d[N];
			N /= f;
			T[ f ]++;
			res1++;
		}
		// Factor res1!
		for ( int i=2; i <= res1; ++i ){
			t = i;
			while ( t > 1 ){
				f = d[t];
				t /= f;
				C[ f ]++;
			}	
		}

		res2 = 1LL;
		int e;
		for ( map<int,int>::iterator it=T.begin(); it != T.end(); ++it ){
			e = it->second;
			if ( e > 1 ){
				for ( map<int,int>::iterator it2=pre[e].begin(); it2 != pre[e].end(); it2++ ){
					C[ it2->first ] -= it2->second;
				}
			}
		}
		for ( map<int,int>::iterator it=C.begin(); it != C.end(); it++ ){
			for ( int i=0; i < it->second; i++ )
				res2 *= it->first;
		}
		printf("%d %lld\n", res1, res2);
	}
	return 0;
}

