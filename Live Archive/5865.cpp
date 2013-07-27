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

struct triple {
	long long w;
	int x,y;
	triple( int X,int Y,int W ){ x=X,y=Y,w=W; }
	triple(){}
	bool operator<(const triple &that) const {
		return w < that.w;
	}
};

const int MAX = 500000;

pii p[1005];
triple E[ MAX ];

int s[ 1005 ];

long long Len( int i , int j ){
	return  (p[i].first - p[j].first)*1LL*(p[i].first - p[j].first) +
			(p[i].second - p[j].second)*1LL*(p[i].second - p[j].second);			
}

void make_set(int x){ s[x] = x; }
int find_set( int x ){ return x != s[x]? ( s[x] = find_set(s[x]) ):(x); }
void link( int x, int y ){
	x = find_set(x);
	y = find_set(y);
	s[y] = x; 
}

int main(){

	int n;
	int m;
	int a,b;
	int res;
	while ( scanf("%d",&n) && (n > 1) ){
		m = 0;
		for ( int j=0; j < n; ++j ){
			make_set(j);
			scanf("%d %d",&p[j].first,&p[j].second);
			for ( int i=0; i < j; ++i ){
				E[m++] = triple( i , j , Len(i,j) );
				if ( m > MAX ) while (1);
			}
		}
		
		scanf("%d %d",&a,&b);
		a--,b--;

		sort( E , E + m );

		for ( int i=0; find_set( a ) != find_set( b ) ; ++i ){
			if ( find_set( E[i].x ) != find_set( E[i].y ) ){
				res = E[i].w;
				link( E[i].x , E[i].y );
			}
		}
		printf("%d\n",res);
	}
	return 0;
}

