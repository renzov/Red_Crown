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

const double EPS = 1e-4;
const int MAXN = 55;

int N;
long double X[MAXN];
long double Y[MAXN];
long double S[MAXN];

long double Xmin, Xmax, Ymin, Ymax;

long double F( const double &x, const double &y ){
	long double res = 0.0;
	long double val;
	for ( int i=0; i < N; ++i ){
		val = ( x - X[i] )*( x - X[i] ) + (y - Y[i])*(y - Y[i]);
		val = sqrtl( val );
		val /= S[i];
		res = max( res, val );
	}
	return res;
}

long double G( const double &x ){
	long double ly = Ymin;
	long double ry = Ymax;
	long double Lres = F( x , ly );
	long double Rres = F( x , ry );
	long double m1, m2;
	long double M1res, M2res;
	int count = 70;
	while ( count-- ){
		m1 = ( 2*ly + ry ) / 3.0;
		m2 = ( ly + 2*ry ) / 3.0;
		
		M1res = F( x , m1 );
		M2res = F( x , m2 );
		if ( M1res <= M2res ){
			ry = m2;
			Rres = M2res;
		}
		else {
			ly = m1;
			Lres = M1res;
		}
	}
	return Lres;
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &N);
		for ( int i=0; i < N; ++i ) scanf("%Lf %Lf %Lf", X+i, Y+i, S+i);
		Xmin = *min_element( X , X + N );
		Xmax = *max_element( X , X + N );
		Ymin = *min_element( Y , Y + N );
		Ymax = *max_element( Y , Y + N );

		long double lx = Xmin;
		long double rx = Xmax;
		long double m1, m2;
		long double Lres = G( lx );
		long double Rres = G( rx );
		long double M1res, M2res;
		int count = 70;

		while ( count-- ){
			m1 = ( 2*lx + rx ) / 3.0;
			m2 = ( lx + 2*rx ) / 3.0;
			M1res = G(m1);
			M2res = G(m2);
			if ( M1res <= M2res ){
				rx = m2;
				Rres = M2res;
			}
			else { 
				lx = m1;
				Lres = M1res;
			}
		}
		printf("%.6Lf\n", Lres );
	}
	return 0;
}

