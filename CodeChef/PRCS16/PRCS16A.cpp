#include<cstdio>
#include<algorithm>
using namespace std;
int main(){
	int A, B, C, W;
	scanf("%d %d %d %d", &A, &B, &C, &W);
	int S = A + B + C - min( A, min(B, C) );
	puts( S >= W? "YES":"NO" );
	return 0;
}
