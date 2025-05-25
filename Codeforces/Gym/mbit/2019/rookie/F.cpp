#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;

int main(){
	
	int N;
	int x, y, r;

	scanf("%d", &N);
	
	int maxX = INT_MIN;
	int minX = INT_MAX;
	int maxY = INT_MIN;
	int minY = INT_MAX;

	for ( int i=0; i < N; ++i ){
		scanf("%d %d %d", &x, &y, &r);
		maxX = max( maxX , x + r );
		maxY = max( maxY , y + r );
		minX = min( minX , x - r );
		minY = min( minY , y - r );
	}
	long long res = ( maxX - minX );
	res *= ( maxY - minY );
	printf("%lld\n", res);
	return 0;
}
