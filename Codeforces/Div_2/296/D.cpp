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

const int MAXN = 200005;

pii I[MAXN];

bool cmp( const pii &a, const pii &b ){
	return a.first + a.second < b.first + b.second;
}

int main(){
	int N;
	int x, w;

	scanf("%d", &N);
	for ( int i=0; i<N; ++i ){
		scanf("%d %d", &x, &w);
		I[i] = pii( x , w );
	}
	sort( I, I + N, cmp );
	int res = 1;
	int last = 0;
	for ( int i=1; i < N; ++i ){
		if ( I[i].first - I[i].second >= I[last].first + I[last].second )
			last = i, res++;
	}
	printf("%d\n", res);
	return 0;
}

