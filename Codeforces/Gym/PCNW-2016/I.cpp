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
const int MAXN = 10000001; 
int N;
long long K;

long long pos[MAXN] = {0};
long long neg[MAXN] = {0};

long long solve( long long X[], int M ){
	int last = 0;
	long long full;
	long long acc = 0;
	long long res = 0;
	long long leftover;
	for ( int i=M; i >= 0; --i ){
		if ( !X[i] ) continue;
		if ( acc > 0 ){
			leftover = min( K - acc, X[i] );
			acc += leftover;
			X[i] -= leftover;
			if ( acc == K ){
				res += 2LL*last;
				acc = 0;
			}
		}
		if ( X[i] > 0 ){ // Pick full trips 	
			full = X[i] / K;
			res += 2LL * full * i;
			X[i] %= K;
		}
		if ( acc == 0 && X[i] > 0 ){ // X[i] < K
			acc += X[i];
			X[i] = 0;
			last = i;
		}
	}
	if ( acc > 0 ){
		res += 2*last;
	}
	return res;
}

int main(){
	int A = 0, B = 0;
	int x, m;

	scanf("%d %I64d", &N, &K);
	for ( int i=0; i < N; ++i ){
		scanf("%d %d", &x, &m);
		if ( x < 0 ) neg[-x] += m, A = max( A, -x );
		else pos[x] += m, B = max( B, x );
	}
	printf("%I64d\n", solve( pos, B ) + solve( neg, A ));
	return 0;
}

