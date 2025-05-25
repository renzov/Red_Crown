#include<cstdio>
#include<algorithm>
using namespace std;
typedef pair<int,int> point;
#define X first
#define Y second
const int MAXN = 10005;

point A[MAXN];
point B[MAXN];

int sgn( const point &a, const point &b, const point &c ){
	int sgnA = 0;
	sgnA = (b.X - a.X)*(c.Y - a.Y) - (c.X - a.X)*(b.Y - a.Y);
	return sgnA > 0? 1:-1;
}

int main(){
	int N;

	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d %d", &A[i].X, &A[i].Y);
		scanf("%d %d", &B[i].X, &B[i].Y);
	}
	
	int Q;
	bool sep;
	point P1, P2;

	scanf("%d", &Q);
	while ( Q-- ){
		scanf("%d %d", &P1.X, &P1.Y);
		scanf("%d %d", &P2.X, &P2.Y);
		sep = false;
		for ( int i=0; i < N; ++i )
			if ( sgn( A[i], B[i], P1 ) != sgn( A[i], B[i], P2 ) )
				sep = not sep;
		puts(sep? "different":"same");
	}
	return 0;
}
