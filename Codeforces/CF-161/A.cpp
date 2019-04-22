#include<algorithm>
#include<cstdio>
using namespace std;

int main(){
	int x;
	for ( int i=0; i < 5; ++i )
		for ( int j=0; j < 5; ++j ){
			scanf("%d", &x);
			if ( x == 1 ){
				printf("%d\n", max( i - 2, 2 - i ) + max(j - 2, 2 - j));
			}
		}

	return 0;
}
