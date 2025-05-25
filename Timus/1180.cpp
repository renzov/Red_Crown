#include<cstdio>
using namespace std;

char N[256];

int main(){

	scanf("%s", N);
	int r = 0;
	for ( int i = 0; N[i]; ++i ){
		r += ( N[i] - '0' );
	}
	r %= 3;
	puts( r? "1":"2");
	if ( r ) 
		printf("%d\n", r);
	return 0;
}
