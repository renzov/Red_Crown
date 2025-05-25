#include<cstdio>
#include<algorithm>
using namespace std;

typedef pair<int,int> pii;
typedef pair<pii, pii> rect;

rect read(){
	int x1, x2, y1, y2;
	scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
	return rect( pii(x1, x2), pii(y1, y2) );
}

int area( const rect &R ){
	if ( R.first.first > R.first.second ) return 0;
	if ( R.second.first > R.second.second ) return 0;
	return (R.first.second - R.first.first) * (R.second.second - R.second.first);
}

bool inside( const pii& A, const int &x ){
	return A.first <= A.second && A.first <= x && x <= A.second;
}

bool covered( const rect &R, const int &x, const int &y ){
	return inside( R.first, x ) && inside( R.second , y );
}

int main(){

	rect A = read();
	rect B = read();

	int x1 = max( A.first.first, B.first.first );
	int y1 = max( A.second.first, B.second.first );
	int x2 = min( A.first.second, B.first.second );
	int y2 = min( A.second.second, B.second.second );
	rect I = rect( pii(x1, x2), pii(y1, y2) );
	
	int cnt = 0;

	if ( covered( I, A.first.first, A.second.first ) )
		cnt++;
	if ( covered( I, A.first.first, A.second.second ) )
		cnt++;
	if ( covered( I, A.first.second, A.second.first ) )
		cnt++;
	if ( covered( I, A.first.second, A.second.second ) )
		cnt++;

	if ( cnt >= 2 )
		printf("%d\n", area(A) - area(I));
	else 
		printf("%d\n", area(A));
	return 0;
}
