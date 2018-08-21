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
#define X first
#define Y second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< long long , int > event;

const int MAXN = 10005;

int N, K;
long long t1, t2;
long long M[MAXN];
long long B[MAXN];
long long E[MAXN];

vector<event> Ev;

int main(){
	long long l, r;
	long long a, b;
	long long x;

	scanf("%d %d %lld %lld", &N, &K, &t1, &t2);
	for ( int i=0; i < N; ++i ) scanf("%lld", M + i);
	for ( int i=0; i < K; ++i ) scanf("%lld %lld", B+i, E+i);

	for ( int i=0; i < N; ++i ){
		a = t1 + M[i], b = t2 + M[i];
		for ( int j=0; j < K; ++j ){
			l = max( a , B[j] );
			r = min( b , E[j] );
			if ( l <= r ){
				Ev.push_back( event( l - M[i], 1 ) );
				Ev.push_back( event( r - M[i], -1 ) );
			}
		}
	}
	sort( Ev.begin(), Ev.end() );
	
	N = (int)Ev.size();
	int open = 0;
	long long res = 0;
	long long lastX = 0;
	int lastO;

	for ( int i=0; i < N;  ){
		lastO = open;
		x = Ev[i].X;
		while ( i < N && x == Ev[i].X ){
			open += Ev[i].Y;
			i++;
		}
		if ( lastO > 0 ){ 
			res += (x - lastX);
		}
		lastX = x;				
	}
	printf("%.7f\n", (double)(t2 - t1 - res) / (t2 - t1));
	return 0;
}

