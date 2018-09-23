#include <cstdio>
#include <set>
#include <cstdlib>
using namespace std;

typedef pair<int,int> point;

const int MAXN = 256;
int X[MAXN];
int Y[MAXN];
set<point> S;

int gcd( const int &x, const int &y ){
	if ( y == 0 ) return x;
	return gcd( y , x % y );
}

int main(){
	int N;
	int x, y, g;
	scanf("%d", &N);
	for ( int i=0; i < N; ++i )
		scanf("%d %d", X+i, Y+i);

	for ( int i=0; i < N; ++i ){
		for ( int j=0; j < i; ++j ){
			x = X[i] - X[j], y = Y[i] - Y[j];
			g = gcd( abs(x), abs(y) );
			x /= g, y /= g;
			if ( S.find( point(x,y) ) == S.end() &&
				 S.find( point(-x, -y) ) == S.end() )
				 	S.insert( point(x,y) );
		}
	}
	printf("%d\n", (int)S.size());
	return 0;
}

