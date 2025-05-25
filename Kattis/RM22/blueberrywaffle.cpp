#include<cstdio>
using namespace std;

int main(){
	int r, f;

	scanf("%d %d", &r, &f);

	int q = f / r;
	int m = f % r;

	if ( m > (r >> 1) )
		q++;

	puts( q & 1? "down":"up");

	return 0;
}
