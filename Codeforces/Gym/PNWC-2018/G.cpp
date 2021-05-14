#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const double EPS = 1e-6;
double X, Y, X1, Y1, X2, Y2;

double Dist( const double &xA, const double &yA, const double &xB, const double &yB ){
	return sqrt( (xA - xB)*(xA - xB) + (yA - yB)*(yA - yB) );
}

int comp( const double &A, const double &B ){
	if ( fabs(A - B) < EPS ) return 0;
	return A < B? -1:1;
}

bool intersect( const double &x, const double &y, const double &r, const double &x1, const double &yA, const double &yB ){
	double diff = (x - x1)*(x - x1);
	if ( comp(r*r, diff) < 0 ) return false;
	double disc = sqrt( r*r - diff );
	double yC = y - disc;
	double yD = y + disc;
	// Now, we check if two axis-parallel segments intersect
	double lb = max( yA, yC );
	double ub = min( yB, yD );
	return comp( lb, ub ) <= 0;
} 

bool check( const double &R ){
	if ( intersect( X, Y, R, X1, Y1, Y2 ) ) return false;
	if ( intersect( X, Y, R, X2, Y1, Y2 ) ) return false;
	if ( intersect( Y, X, R, Y1, X1, X2 ) ) return false;
	if ( intersect( Y, X, R, Y2, X1, X2 ) ) return false;
	return true;
}

int main(){

	scanf("%lf %lf %lf %lf %lf %lf", &X, &Y, &X1, &Y1, &X2, &Y2);
	double l = 0.0;
	double r = min( Dist( X, Y, X1, Y1 ), Dist(X, Y, X1, Y2) );
	r = min( r, Dist( X, Y, X2, Y1 ) );
	r = min( r, Dist( X, Y, X2, Y2 ) );
	double m;

	while ( r - l > EPS ){
		m = ( l + r ) / 2.0;
		if ( check(m) ) 
			l = m;
		else 
			r = m;
	}
	printf("%0.3f\n", round( 1000.0 * l )/1000.0 );
	return 0;
}
