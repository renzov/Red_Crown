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

const int MAXN = 2005;

int N;
long long S, T;
multiset<long long> V;
long long a[MAXN];

long long calc_time( const long long &t, long long s ){
	return (((s-1)*s) >> 1) + s*t;
}

long long get_time_simulation( long long act ){
	multiset<long long> P = V;
	multiset<long long>::iterator it;
	long long res = 0;
	while ( !P.empty() ){
		it = P.lower_bound( act );
		if ( it == P.end() ) it = P.begin();
		res += (( *it - act + S )%S);
		res += T;
		act = (*it + T)%S;
		P.erase(it);
	}
	return res;
}

int main(){
	long long resmin, resmax, resavg;
	long long t;
	long long v;
	int M;
	while (scanf("%d %lld %lld", &N, &S, &T) != EOF){
		resmin = LLONG_MAX, resmax = 0, resavg = 0;
		V.clear();
		for ( int i=0; i < N; ++i ){ 
			scanf("%lld", a+i); 
			V.insert( a[i] );
		}
		sort( a , a + N);
		long long size;
		M = unique( a, a + N ) - a;
		long long prev = a[M-1] - S;
		for ( int i=0; i < M; i++ ){
			size = a[i] - prev;
			t = get_time_simulation( a[i] );
			resmin = min( resmin, t );
			resmax = max( resmax, size + t - 1 );
			resavg += calc_time( t, size ); 
			prev = a[i];
		}
		long long g = __gcd( S, resavg );
		printf("%lld\n%lld\n%lld/%lld\n", resmin, resmax, resavg/g, S/g);
	}
	return 0;
}

