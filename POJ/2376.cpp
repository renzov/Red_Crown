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

const int MAXN = 25005;

pii I[MAXN];

bool intersect( int x1, int y1, int x2, int y2 ){
	return max(x1,x2) <= min(y1,y2); 
}

int main(){

	int N,T;
	int res,tmp;

	scanf("%d %d",&N,&T);

	for ( int i=0; i < N; ++i )
		scanf("%d %d",&I[i].first,&I[i].second);
		
	sort( I , I + N );

	int last = 1;

	int p = 0;

	if ( I[p].first > 1 ){
		puts("-1");
		return 0;
	}
	res = 0;
	do {
		tmp = -1;
		while ( p < N && intersect( 1 , last , I[p].first , I[p].second ) ){
			tmp = max( tmp , I[p].second );
			p++;
		}
		if ( tmp < last ) break;
		last = tmp + 1;
		res++;
	}
	while ( last <= T );
	if ( last <= T ) puts("-1");
	else printf("%d\n",res);

	return 0;
}

