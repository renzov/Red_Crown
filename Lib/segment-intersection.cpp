#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

#define X first
#define Y second

typedef pair<int,int> point;

point operator+( const point &A, const point &B ){
	return point( A.X + B.X, A.Y + B.Y );
}
point operator-( const point &A, const point &B ){
	return point( A.X - B.X, A.Y - B.Y );
}
point operator*( const point &A, const int &s ){
	return point( s * A.X , s * A.Y );
}
point operator*( const int &s, const point &A ){
	// scalar product
	return point( s * A.X , s * A.Y );
}
long long operator*( const point &A, const point &B ){
	// dot product
	return A.X * B.X + A.Y * B.Y;
}
long long operator^( const point &A, const point &B ){
	// cross product
	return 1LL * A.X * B.Y - 1LL * B.X * A.Y;
}

int sign( const point &A, const point &B, const point &C ){
	long long cr = (B - A) ^ (C - A);
	if ( !cr ) return cr;
	return ( cr < 0 )? -1:1;
}

int len( const point &A ){
	// norm of a vector
	return sqrt( A * A );
}

bool between( const point &A, const point &B, const point &C ){
	return min( B.X, C.X ) <= A.X && A.X <= max( B.X, C.X ) && min( B.Y, C.Y ) <= A.Y && A.Y <= max( B.Y, C.Y );
}

int main(){

	int t;
	int x1, x2, x3, x4;
	int y1, y2, y3, y4;

	scanf("%d", &t);
	while ( t-- ){
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		scanf("%d %d %d %d", &x3, &y3, &x4, &y4);

		point A(x1, y1);
		point B(x2, y2);
		point C(x3, y3);
		point D(x4, y4);

		int sC = sign( A, B, C );
		int sD = sign( A, B, D );
		int sA = sign( C, D, A );
		int sB = sign( C, D, B );

		if ( sA * sB > 0 || sC * sD > 0 ){
			puts("NO");
		}
		else if ( sA * sB < 0 && sC * sD < 0 ){
			puts("YES");
		}
		else if ( (sA == 0 && between( A, C, D )) || (sB == 0 && between(B, C, D)) || 
				  (sC == 0 && between( C, A, B )) || (sD == 0 && between( D, A, B )) ){
			puts("YES");
		}
		else {
			puts("NO");
		}

	}

	return 0;
}
