#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
#define X first
#define Y second
typedef pair<double,double> point; 
const int MAXN = 100005;
const double EPS = 10e-6;
int N;

int T[MAXN], V[MAXN];
point P[MAXN];
point L[MAXN], U[MAXN];

int cmp( const double a, const double b ){
	if ( fabs(a-b) < EPS ) return 0;
	return (a<b)? -1:1;
}

double area2( const point &A, const point &B, const point &C ){
	return (B.X-A.X)*(C.Y-A.Y) - (C.X - A.X)*(B.Y - A.Y);
}

double get_interX( const double m1, const double &b1, const double &m2, const double &b2 ){
	return (b1 - b2) / (m2 - m1);
}

void add_points( point E[], const int &size, vector<double> &x ){
	for ( int i=0; i < (size-1); ++i ){
		x.push_back( get_interX( E[i].X, -E[i].Y, E[i+1].X, -E[i+1].Y ) );
	}
}

void get_envelope( point E[], int &size ){
	if ( N == 1 ){
		size = 1;
		E[0] = P[0];
		return;
	}
	int i = 0;
	while ( i < ( N - 1 ) && (cmp(P[i].X, P[i+1].X) == 0) ) i++;
	size = 1, E[0] = P[i];
	i++;
	for ( ; i < N; ++i ){
		while ( size > 1 && cmp ( area2( E[size-2], E[size-1], P[i] ), 0.0 ) >= 0 )
			size--;
		E[size++] = P[i];
	}
	reverse( E, E + size );
}

inline double f( const double &m, const double &b, const double &x ){ return m*x + b; }

bool compare( const point &A, const point &B ){
	if ( cmp( A.X, B.X ) == 0 ) return cmp( A.Y, B.Y ) < 0;
	return cmp( A.X, B.X ) < 0;
}

int main(){
	int n, m;
	while ( scanf("%d", &N) && N ){
		for ( int i=0; i < N; ++i ){ 
			scanf("%d %d", T+i, V+i);
			P[i] = point( 1.0*V[i], 1.0*V[i]*T[i] );
		}
		double maxT = 1.0*(*max_element(T, T+N));
		// Get upper and lower hull
		sort( P , P + N, compare );
		get_envelope( U, n );
		reverse( P, P + N );
		get_envelope( L, m );
		// from each line get the intersection points 
		vector<double> x;
		add_points( U, n, x );
		add_points( L, m, x );
		x.push_back( maxT );
		sort( x.begin(), x.end() );
		int a = 0, b = 0; // pointers for upper/lower envelope current segment  
		double res = 10e10;
		double l1, l2;
		for ( int i=0; i < (int)x.size(); ++i ){
			if ( i && cmp( x[i], x[i-1] ) == 0 ) continue;
			// test if need to advance envelope pointer
			if ( a < (n-1) && cmp( f(U[a].X, -U[a].Y, x[i]) , f(U[a+1].X, -U[a+1].Y, x[i]) ) == 0 )
				a++;
			if ( b < (m-1) && cmp( f(L[b].X, -L[b].Y, x[i]) , f(L[b+1].X, -L[b+1].Y, x[i]) ) == 0 )
				b++;
			if ( cmp(x[i], maxT) < 0 ) continue;
			l1 = f( U[a].X, -U[a].Y, x[i] );
			l2 = f( L[b].X, -L[b].Y, x[i] );
			res = min( res, fabs(l1-l2) );
		}
		printf("%f\n", res);
	}
	return 0;
}
