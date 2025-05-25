#include<cstdio>
#include<algorithm>
using namespace std;
typedef pair<long long, long long> pii;
typedef pair<pii, pii> rect;

rect emptyRect = rect( pii(0, -1), pii(0, -1) );

rect read(){
	long long x1, x2, y1, y2;
	scanf("%lld %lld %lld %lld", &x1, &y1, &x2, &y2);
	return rect( pii(x1, x2), pii(y1, y2) );
}

rect intersection( const rect &A, const rect &B ){
	if ( A.first.first > A.first.second ) return emptyRect;
	if ( A.second.first > A.second.second ) return emptyRect;

	if ( B.first.first > B.first.second ) return emptyRect;
	if ( B.second.first > B.second.second ) return emptyRect;

	long long x1 = max( A.first.first, B.first.first );
	long long x2 = min( A.first.second, B.first.second );
	long long y1 = max( A.second.first, B.second.first );
	long long y2 = min( A.second.second, B.second.second );
	return rect( pii(x1, x2), pii(y1, y2) );
}

long long area( const rect &R ){
	if ( R.first.first > R.first.second ) return 0;
	if ( R.second.first > R.second.second ) return 0;
	return ( R.first.second - R.first.first ) * ( R.second.second - R.second.first );
}

int main(){	

	rect A = read();
	rect B = read();
	rect C = read();

	rect I1 = intersection( A, B );
	rect I2 = intersection( A, C );

	long long res = area(A) - area(I1) - area(I2);

	rect I3 = intersection( I1, I2 );
	rect I4 = intersection( A, I3 );

	res += area( I4 );

	if ( res > 0 ) puts("YES");
	else puts("NO");

	return 0;
}
