#include<cstdio>
using namespace std;

int main(){
	int res = 0;
	int N;
	int cnt, x;

	scanf("%d", &N);
	while ( N-- ){
		cnt = 0;
		for ( int i=0;  i < 3; ++i ){
			scanf("%d", &x);
			if ( x ) cnt++;
		}
		if ( cnt > 1 ) res++;
	}
	printf("%d\n", res);
	return 0;
}
