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
int len( const point &A ){
	// norm of a vector
	return sqrt( A * A );
}

int main(){
	return 0;
}
