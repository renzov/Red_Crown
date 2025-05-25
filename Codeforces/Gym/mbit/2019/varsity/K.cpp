#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
typedef pair<double, int> event;
typedef pair<double, double> point;
const int MAXN = 100005;
const double EPS = 1e-9;
#define X first
#define Y second

vector<event> E;
point P[MAXN];
double TP[MAXN];

point Q[MAXN];
double TQ[MAXN];

int cmp( const double &a, const double &b ){
	if ( fabs(a - b) < EPS ) return 0;
	return a < b? -1:1;
}

double dist( const point &A, const point &B ){
	return sqrt( (A.X - B.X)*(A.X - B.X) + (A.Y - B.Y)*(A.Y - B.Y) );
}

point advance( const point &p1, const double &t1, const point &p2, const double &t2, const double &t ){
	point v = point( p2.X - p1.X, p2.Y - p1.Y );
	double dt = (t - t1) / (t2 - t1);
	return point( p1.X + dt * v.X, p1.Y + dt * v.Y );
}

double solve( const point &A, const point &B, const point &C, const point &D ){
	point V = point( B.X - A.X, B.Y - A.Y );
	point W = point( D.X - C.X, D.Y - C.Y );

	double dx = A.X - C.X;
	double dy = A.Y - C.Y;
	double dvx = V.X - W.X;
	double dvy = V.Y - W.Y;

	double b = 2 * ( dx * dvx + dy * dvy );
	double a = dvx * dvx + dvy * dvy;

	double opt = -b / (2 * a);
	if ( cmp( opt, 0.0 ) >= 0 && cmp( opt, 1.0 ) <= 0 ){
		point p1 = point( A.X + V.X * opt, A.Y + V.Y * opt ); 
		point p2 = point( C.X + W.X * opt, C.Y + W.Y * opt ); 
		return dist( p1, p2 );
	}
	else { 
		return min( dist( A, C ), dist( B, D ) );
	}
} 


int main(){

	int N, M, G, A;

	scanf("%d %d %d %d", &N, &M, &G, &A );
	for ( int i=0; i < N; ++i )
		scanf("%lf %lf", &P[i].X, &P[i].Y );
	P[N] = P[0];

	for ( int i=0; i < M; ++i )
		scanf("%lf %lf", &Q[i].X, &Q[i].Y );
	Q[M] = Q[0];

	double t;
	double len;
	// create events for the first polygon
	TP[0] = 0.0;
	t = 0.0;
	for ( int i=1; i < N; ++i ){
		len = dist( P[i], P[i - 1] ) / G;
		t += len;
		TP[i] = t;
		E.push_back( event( t, 0 ) );
	}
	// create events for the second polygon
	t = 0.0;
	TQ[0] = 0.0;
	for ( int i=1; i < M; ++i ){
		len = dist( Q[i], Q[i - 1] ) / A;
		t += len;
		TQ[i] = t;
		E.push_back( event( t , 1 ) );
	}
	
	sort( E.begin(), E.end() );
	// Process events by time
	double res = 1e20;
	double nt;
	int p, q;
	point a, b, c, d;

	t = 0.0;
	for ( int i=0; i < (int)E.size(); ++i ){
		nt = E[i].first;
		//printf("t = %f - nt = %f\n", t, nt);
		if ( fabs( t - nt ) > EPS ){
			if ( cmp( t, TP[N - 1] ) < 0 ){
				a = advance( P[p], TP[p], P[p + 1], TP[p + 1], t );
				b = advance( P[p], TP[p], P[p + 1], TP[p + 1], nt );
			}
			else {
				a = b = P[N - 1];
			}
			if ( cmp( t, TQ[M - 1] ) < 0 ){
				c = advance( Q[q], TQ[q], Q[q + 1], TQ[q + 1], t );
				d = advance( Q[q], TQ[q], Q[q + 1], TQ[q + 1], nt );
			}
			else {
				c = d = Q[M - 1];
			}
			res = min( res, solve( a, b, c, d ) );
		}
		if ( E[ i ].second ) q++;
		else p++;
		t = nt;
	}
	printf("%lld\n", (long long)round(res) );
	return 0;
}

