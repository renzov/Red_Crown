#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;

int main(){
	int x1, x2;
	int y1, y2;

	scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
	int dx = abs( x1 - x2 );
	int dy = abs( y1 - y2 );
	int res = min( dx, dy );
	
	dx -= res, dy -= res;
	res += dx; 
	res += dy;
	printf("%d\n", res);

	return 0;
}
