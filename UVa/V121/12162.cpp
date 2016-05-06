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
int Y[2*MAXN];

struct seg {
	int A, B, C;
	point p1, p2;
	seg(){}
	seg( point p, point q ){
		if ( p.Y > q.Y ) p1 = q, p2 = p;
		else p1 = p, p2 = q;
		B = p2.X - p1.X; //dx
		A = -p2.Y + p1.Y; //-dy
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
	
	double find_length( int y ){
		double X[MAXN];
		int m = 0;
		for ( int i=0; i < n; ++i ){
			if ( S[i].A != 0 && y >= S[i].p1.Y && y <= S[i].p2.Y ){
				X[ m++ ] = S[i].get_X( y );
			}
			sort( X , X + m );
			double res = 0.0;
			for ( int i=0;  i < (m-1); i+=2 ){
				res += (X[i+1] - X[i]);
			}
			return res;
		}
	}


};

int main(){
	
	int runs;
	point P[MAXN];
	int N;
	int M;

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &N);
		for ( int i=0; i < N; ++i ){
			scanf("%d %d", &P[i].X, &P[i].Y);
			Y[i] = P[i].Y;
		}
		poly A( P, N );
		scanf("%d", &N);
		for ( int i=0; i < N; ++i ){
			scanf("%d %d", &P[i].X, &P[i].Y);
			Y[N+i] = P[i].Y;		
		}
		poly B( P , N );
		sort( Y, Y + 2*N );
		M = unique( Y , Y + 2*N ) - Y;
		
	}
	return 0;
}

