#include<cstdio>
using namespace std;

int main(){
	int A, B;
	char r;
	int diff;

	scanf("%d %d %c", &A, &B, &r);
	
	if ( r == 'w' ){
		diff = B / 10;
		A += diff;
	}
	else {
		diff = A / 10;
		A -= diff;
	}
	printf("%d\n", A);
	return 0;
}
