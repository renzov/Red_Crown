#include<cstdio>
#include<algorithm>
using namespace std;

inline int inter( const int &A, const int &B, const int &C, const int &D ){
	return max( 0, min( B, D ) - max(A, C) ); 
}

int main(){

	int A, B, C, D;

	scanf("%d %d %d %d", &A, &B, &C, &D);
	// Area of Union 
	printf("%d\n", (B - A) + (D - C) - inter(A, B, C, D) );

	return 0;
}
