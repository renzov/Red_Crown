#include<cstdio>
using namespace std;

int main(){
	int M, A, B, C;
	// Pigeon-hole principle
	scanf("%d %d %d %d", &M, &A, &B, &C);
	if ( A + B + C <= 2*M ) puts("possible");
	else puts("impossible");
	return 0;
}
