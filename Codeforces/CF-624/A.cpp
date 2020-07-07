#include<cstdio>
using namespace std;

int main(){
	int T;
	int A, B;
	scanf("%d", &T);
	while ( T-- ){
		scanf("%d %d", &A, &B);
		if ( A < B ){
			if ((B - A) & 1) puts("1");
			else puts("2");
		}
		else if ( B < A ){
			if ((B - A) & 1) puts("2");
			else puts("1");
		}
		else {
			puts("0");
		}
	}

	return 0;
}
