#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
typedef pair<double, int> event;
typedef pair<double, double> point;
const int MAXN = 100005;
const double EPS = 1e-10;
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

point advance( const point &p1, const point &p2, const double &S, const double &T ){
	double ratio = S * T / dist( p1, p2 );
	point delta = point( (p2.X - p1.X) * ratio, (p2.Y - p1.Y) * ratio );
	return point( p1.X + delta.X, p1.Y + delta.Y );
}

double solve( const point &A, const point &B, const point &C, const point &D, const double &dt ){
	point V = point( (B.X - A.X) / dt, (B.Y - A.Y) / dt );
	point W = point( (D.X - C.X) / dt, (D.Y - C.Y) / dt );

	double dx = A.X - C.X;
	double dy = A.Y - C.Y;
	double dvx = V.X - W.X;
	double dvy = V.Y - W.Y;

	double b = 2 * ( dx * dvx + dy * dvy );
	double a = dvx * dvx + dvy * dvy;

	double opt = -b / (2 * a);
	if ( cmp( opt, 0.0 ) >= 0 && cmp( opt, dt ) <= 0 ){
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

	for ( int i=0; i < M; ++i )
		scanf("%lf %lf", &Q[i].X, &Q[i].Y );

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
	double res = dist(P[0], Q[0]);
	double nt;
	double dt;
	int p = 0, q = 0;
	t = 0.0;

	point curP, nxtP;
	point curQ, nxtQ;

	curP = P[0], curQ = Q[0];
	for ( int i=0; i < (int)E.size(); ++i ){
		nxtP = curP, nxtQ = curQ;
		nt = E[i].first;
		dt = nt - t;
		if ( E[i].second ){ // advance Q
			q++;
			nxtQ = Q[q];
			if ( p < N - 1 )
				nxtP = advance( curP, P[p + 1], (double)A, dt );
		}
		else {	// advance Q
			p++;
			nxtP = P[p];
			if ( q < M - 1 )
				nxtQ = advance( curQ, Q[q + 1], (double)G, dt );
		}
		if ( fabs( dt ) > EPS )
			res = min( res, solve( curP, nxtP, curQ, nxtQ, dt ) );
		t = nt;
		curP = nxtP;
		curQ = nxtQ;
	}
	printf("%lld\n", (long long)round(res) );
	return 0;
}
