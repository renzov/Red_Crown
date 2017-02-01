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
typedef pair< int, int > pii;
typedef pair< double , double > point;

const double EPS = 0.00001;
const int MAXN = 305;

point P[ MAXN * MAXN ];

int cmp( const double &x , const double &y ){
	if ( fabs( x - y ) < EPS ) return 0;
	return x < y? -1:1;
}

bool operator==( const point &A, const point &B ){
	return !cmp( A.X, B.X ) && !cmp( A.Y, B.Y );
}

bool operator<( const point &A, const point &B){
	int d1 = cmp( A.X, B.X );
	int d2 = cmp( A.Y, B.Y );
	if ( d1 != 0 ) return d1 < 0;
	return d2 < 0;
} 

struct seg {
	point st, en;
	double m, b;
	bool hor;
	seg( point x , point y ){
		st = x, en = y;
		calc();
	}
	
	void calc(){
		if ( cmp( st.X, en.X ) != 0 ){
			m = ( st.Y - en.Y ) / ( st.X - en.X );
			if ( fabs( m ) < EPS ) m = 0.0;
			b = st.Y - m * st.X;
			hor = false;
		}
		else {
			hor = true;
		}
	}
};

int main(){

	int V, N;
	int x, y;
	while ( scanf("%d", &N) && N > 3 ){
		for ( int i=0; i < N; ++i ){
			scanf("%d %d", &x, &y);
		
		
		}
	
	
	}
	return 0;
}

