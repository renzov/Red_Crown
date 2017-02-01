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
const double EPS = 0.00001;
struct point {
	int x,y,v,l,id;
	bool operator<(const point &that) const {
		return ( x == that.x )? (y < that.y):(x < that.x);
	}
};

inline int areaS( point &a, point &b, point &c ){
	return (b.x - a.x)*( c.y - a.y ) - ( c.x - a.x )*( b.y - a.y ); 
}

double perimeter( point *P , int size ){
	if ( size == 1 ) return 0.0;
	//convex hull finding
	point lower[20];
	lower[0] = P[0]; lower[1] = P[1];
	int L = 2;
	
	for ( int i=2; i<size ; ++i ){
		while ( L > 1 && areaS( lower[L-2] , lower[L-1] , P[i] ) <= 0 )
			L--;
		lower[L++] = P[i];
	}

	point upper[20];
	upper[0] = P[size-1]; upper[1] = P[size-2];
	int U = 2;

	for ( int i=size-3; i >= 0 ; --i ){
		while ( U > 1 && areaS( upper[U-2] , upper[U-1] , P[i] ) <= 0 )
			U--;
		upper[U++] = P[i];
	}

	for ( int i=1; i < U ; ++i )
		lower[L++] = upper[i];

	
	double len = 0.0;

	for ( int i=0; i < (L-1); ++i )
		len += hypot( lower[i].x - lower[i+1].x , lower[i].y - lower[i+1].y );

	return len;
}

int main(){
	int total;
	int n;
	int m;
	point T[20];
	int runs = 0;

	int val;

	int best,bm,bmask;
	double extra;

	while ( scanf("%d",&n) && n ){
		runs++;
		vector<point> P(n);

		for ( int i=0; i < n; ++i ){
			scanf("%d %d %d %d",&P[i].x,&P[i].y,&P[i].v,&P[i].l);
			P[i].id = i+1;
		}
		
		sort( all(P) );
		best = INT_MAX;

		for ( int mask=1; mask < (1<<n) ; ++mask ){
			total = 0;
			val = 0;
			m = 0;
			for ( int i=0; i < n; ++i )
				if ( !((mask >> i)&1) ){
					total += P[i].l;
					val += P[i].v;
				}
				else {
					T[m++] = P[i];
				}

			double len = perimeter( T , m );
			
			if ( len < total || fabs( len - total ) < EPS ){
				if ( val < best || ( val == best && m < bm ) ){
					best = val;
					bm = m;
					extra = total - len;
					bmask = mask;
				}
			}
		}

		if ( runs > 1 )	puts("");
		int a[20];
		int t = 0;
		for ( int i=0; i < n; ++i ){
			if ( !((bmask >> i)&1) ){
				a[t++] = P[i].id;
			}
		}
		sort ( a , a + t );
		printf("Forest %d\n",runs);
		printf("Cut these trees:");
		for ( int i=0; i < t; ++i ){
			printf(" %d",a[i]);
		}
		puts("");
		printf("Extra wood: %.2lf\n",extra);
	}
	return 0;
}

