#include<cstdio>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

#define X first
#define Y second 
const double EPS = 1e-6;

typedef pair<double, double> point;
typedef vector<point> poly;
point O;

double dist2( const point &A, const point &B ){
	return (A.X - B.X)*(A.X - B.X) + (A.Y - B.Y)*(A.Y - B.Y);
}

double det( const double &a1, const double &a2, const double &b1, const double &b2 ){
	return a1 * b2 - b1 * a2;
}

struct Line {
	double A;
	double B;
	double C;
	Line( const point &p, const point &q ){
		// vector pq
		point V = point( q.first - p.first, q.second - p.second );
		point norm = point( -V.second, V.first );
		A = norm.first, B = norm.second;
		C = -(norm.first * p.first + norm.second * p.second); 
	}
};

double area2( const point &A, const point &B, const point &C ){
	return (B.X - A.X)*(C.Y - A.Y) - (C.X - A.X)*(B.Y - A.Y);
}

int sgn( const point &A, const point &B, const point &C ){
	double a = area2( A, B, C );
	if ( fabs(a) < EPS ) return 0;
	return ( a < 0 )? -1:1;
}

bool angCmp( const point &A, const point &B ){
	int s = sgn( O, A, B );
	if ( s != 0 ) 
		return s > 0;
	else
		return dist2( A, O ) < dist2( B, O );
}

bool inside( point &p, poly &P ){
	// Polygon is in ccw orientation
	for ( int i=1; i < (int)P.size(); ++i ){
		if ( sgn( P[i - 1], P[i], p ) < 0 ) return false;
	}
	return true;
}

point intersection( point &A, point &B, point &C, point &D ){
	Line L1(A, B);
	Line  L2(C, D);
	double den = det( L1.A, L1.B, L2.A, L2.B );
	double x = det( -L1.C, L1.B, -L2.C, L2.B ) / den;
	double y = det( L1.A, -L1.C, L2.A, -L2.C ) / den;
	return point(x, y);
}

bool intersect( point &A, point &B, point &C, point &D ){
	// Test proper intersection
	int s1 = sgn( A, B, C );
	int s2 = sgn( A, B, D );
	int t1 = sgn( C, D, A );
	int t2 = sgn( C, D, B );
	if ( s1 && s2 && t1 && t2 )
		return ( s1 != s2 && t1 != t2 );
	else 
		return false;
}

poly convexHull( poly &P ){
	sort( P.begin(), P.end() );
	O = P[0];
	sort( P.begin(), P.end(), angCmp );
	
	poly R;
	R.push_back( P[0] );
	R.push_back( P[1] );
	int size = 2;

	for ( int i=2; i < (int) P.size(); ++i ){
		while ( size > 1 && sgn( R[size - 2], R[size - 1], P[i] ) <= 0 ){
			R.pop_back();
			size--;
		}
		R.push_back( P[i] ); size++;
	}
	R.push_back( P[0] );
	return R;
}

poly intersect( poly &P, poly &Q ){
	poly R;
	
	for ( int i=0; i < (int)P.size() - 1; ++i )
		if ( inside( P[i], Q ) )
			R.push_back( P[i] );
	
	for ( int i=0; i < (int)Q.size() - 1; ++i )
		if ( inside( Q[i], P ) )
			R.push_back( Q[i] );
	
	point p;
	for ( int i=0; i < P.size(); ++i )
		for ( int j=0; j < Q.size(); ++j ){
			if ( intersect( P[i], P[i+1], Q[j], Q[j + 1] ) ){
				p = intersection( P[i], P[i + 1], Q[j], Q[j + 1] );
				R.push_back( p );
				break;
			}
		}
	R = convexHull( R );
	return R;
}

poly readPolygon(){
	poly P;
	int n;
	scanf("%d", &n);
	P.resize( n + 1 );
	for ( int i=0; i < n; ++i )
		scanf("%lf %lf", &P[i].X, &P[i].Y);
	P[n] = P[0];
	return P;
}

double area2( poly &P ){
	if ( (int)P.size() < 3 ) return 0;
	// Find the area of the polygon
	double res = 0.0;
	for ( int i=2; i < P.size() - 1; ++i )
		res += area2( P[0], P[i - 1], P[i] );
	return res;
}

int main(){
	int N;
	scanf("%d", &N);
	
	poly P,Q;

	P = readPolygon();
	for ( int i=1; i < N; ++i ){
		Q = readPolygon();
		P = intersect( P, Q );
	}
	printf("%.5f\n", area2( P )/2.0 );
	return 0;
}
