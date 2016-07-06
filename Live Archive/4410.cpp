#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <climits>

#define X first
#define Y second
using namespace std;
typedef pair< int , int > point;

const int MAXN = 55;

struct seg {
	int A, B, C;
	point p1, p2;
	seg(){}
	seg( point p, point q ){
		if ( p.Y > q.Y ) p1 = q, p2 = p;
		else p1 = p, p2 = q;
		B = p2.X - p1.X; //dx
		A = p1.Y - p2.Y; //-dy
		C = -A*p1.X - B*p1.Y; 
	}
	double get_X( int y ){
		return (-1.0*B*y - C) / A;
	}
};


struct poly {
	int n;
	seg S[MAXN];
	int minY;
	int maxY;
	poly( point P[], int N ){ // P[0] = P[N]
		minY = INT_MAX;
		maxY = -INT_MAX;
		for ( int i=0; i < N; ++i ){
			if ( P[i].Y < minY ) minY = P[i].Y;
			if ( P[i].Y > maxY ) maxY = P[i].Y;
			S[i] = seg( P[i] , P[i+1] );
		}
		n = N;
	}
	
	double find_length( int y, bool low ){
		double X[MAXN];
		int m = 0;
		for ( int i=0; i < n; ++i ){
			if ( S[i].A != 0 && y >= S[i].p1.Y && y <= S[i].p2.Y ){
				if ( low && S[i].p2.Y > y ){ 
					X[ m++ ] = S[i].get_X( y );
				}
				else if (!low && S[i].p1.Y < y ){
					X[ m++ ] = S[i].get_X( y );				
				}
			}
		}
		sort( X , X + m );
		double res = 0.0;
		for ( int i=0;  i < (m-1); i+=2 ){
			res += (X[i+1] - X[i]);
		}
		return res;
	}
};

long double area( double A, double B, double C, double D ){
	long double D1 = B - A;
	long double D2 = D - C; 
	return D1*D2/3.0 + (A*D2 + C*D1)/2.0 + (long double)A*C; 
}

int main(){
	
	int runs;
	point P[MAXN];
	int N;
	int M;
	int cases = 0;
	scanf("%d", &runs);
	while ( runs-- ){
		cases++;
		scanf("%d", &N);
		for ( int i=0; i < N; ++i ){
			scanf("%d %d", &P[i].X, &P[i].Y);
		}
		P[N] = P[0];
		poly A( P, N );
		scanf("%d", &N);
		for ( int i=0; i < N; ++i ){
			scanf("%d %d", &P[i].X, &P[i].Y);
		}
		P[N] = P[0];
		poly B( P , N );
		
		int low = max( A.minY, B.minY );
		int high = min( A.maxY, B.maxY );
		double l1,l2,r1,r2;
		long double res = 0.0;
		for ( int i=low; (i + 1) <= high; ++i ){
			l1 = A.find_length( i , true );
			r1 = B.find_length( i , true );
			l2 = A.find_length( i+1 , false );
			r2 = B.find_length( i+1 , false );
			res += area( l1, l2, r1, r2 );
		}
		printf("Case %d: %.6Lf\n", cases, res);
	}
	return 0;
}
