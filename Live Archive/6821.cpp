#include<cstdio>
using namespace std;

int main(){
	int A[10], B;
	while ( scanf("%d %d %d %d %d", A, A + 1, A + 2, A + 3, A + 4) == 5 ){
		bool ok = true; 
		for ( int i=0; i < 5; ++i ){
			scanf("%d", &B);
			ok &= ( B xor A[i] );
		}
		puts( ok? "Y":"N");
	}
	return 0;
}
