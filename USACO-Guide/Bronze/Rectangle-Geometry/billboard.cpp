#include<cstdio>
#include<algorithm>
using namespace std;

typedef pair<int,int> pii;
typedef pair<pii, pii> rect;

int area( const rect& R ){
	int l = max( 0, R.first.second - R.first.first );
	int r = max( 0, R.second.second -  R.second.first);
	return l * r;
}

rect read(){
	int x1, y1, x2, y2;
	scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
	return rect( pii( x1, x2 ), pii(y1, y2) ); 
}

int main(){
	int res = 0;

	rect R1 = read();
	rect R2 = read();
	rect I = read();
	
	res += area( R1 );
	res += area( R2 );

	rect I1 = rect( pii( max( R1.first.first, I.first.first ), min( R1.first.second, I.first.second) ), 
					pii( max( R1.second.first, I.second.first ), min( R1.second.second, I.second.second ) ) );
	res -= area( I1 );
	rect I2 = rect( pii( max( R2.first.first, I.first.first ), min( R2.first.second, I.first.second) ), 
					pii( max( R2.second.first, I.second.first ), min( R2.second.second, I.second.second ) ) );

	res -= area( I2 );

	printf("%d\n", res);
	return 0;
}
