#include<cstdio>
using namespace std;

int main(){

	int A, B;
	int C, D;
	int val;
	scanf("%d %d %d %d", &B, &A, &D, &C);

	// First equation represented as Ax - B
	// Second equation represented as Cx - D
	
	for ( int i = 1; ; ++i ){
		val = A * i - B;	
		if ( !((val + D) % C) ){
			printf("%d\n", val );
			break;
		}
	}
	return 0;
}
