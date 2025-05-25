#include<cstdio>
using namespace std;

int main(){
	int A, B, C;

	while ( scanf("%d %d %d", &A, &B, &C) == 3 ){
		int sum = A + B + C;
		if ( sum == 0 || sum == 3 )
			puts("*");
		else if ( A != B && A != C ) puts("A");
		else if ( B != A && B != C ) puts("B");
		else puts("C");
	}
	return 0;
}
