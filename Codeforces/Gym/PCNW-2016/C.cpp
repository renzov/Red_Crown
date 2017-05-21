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

const int MAXN = 100005;

bool up[MAXN] = {0};

int main(){
	int N, K, R;
	int x;
	int res = 0;
	scanf("%d %d %d", &N, &K, &R);
	for ( int i=0; i < K; ++i ){
		scanf("%d", &x);
		x--;
		up[x] = true;
	}
	// begin the sliding window
	deque<int> dq;
	int cnt = 0;

	for ( int i=0; i < R; ++i ){
		if ( up[i] ) cnt++;
		else dq.push_back( i );
	}
	while ( cnt < 2 ){
		x = dq.back();
		dq.pop_back();
		up[x] = true;
		cnt++;
		res++;
	}

	for ( int i=1; (i + R) <= N; ++i ){
		while ( !dq.empty() && dq.front() < i ) dq.pop_front();
		if ( up[i-1] ) cnt--;

		if ( up[i + R - 1] ) cnt++;
		else dq.push_back( i + R - 1 );

		while ( cnt < 2 ){
			x = dq.back();
			dq.pop_back();
			up[x] = true;
			cnt++;
			res++;
		}
	}
	printf("%d\n", res);
	return 0;
}

