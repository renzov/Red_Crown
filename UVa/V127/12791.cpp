#include<cstdio>
using namespace std;

void process( const int &X, const int &Y ){
	int D = Y - X;	
	printf("%d\n", Y / D + ( Y % D != 0 ) );
}

int main(){
	int X, Y;
	while ( scanf("%d %d", &X, &Y) == 2 )
		process( X, Y );
	return 0;
}
