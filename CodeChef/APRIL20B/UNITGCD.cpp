#include<cstdio>
using namespace std;

void process(){
	int N;	
	scanf("%d", &N);
	if ( N == 1 ){
		printf("1\n1 1\n");
	}
	else if ( N == 2 ){
		printf("1\n2 1 2\n");	
	}
	else {
		printf("%d\n", N >> 1);
		printf("3 1 2 3\n");
		for ( int i=4; i <= N; i += 2 ){
			if ( i + 1 <= N ){
				printf("%d %d %d\n", 2, i, i + 1);
			}
			else {
				printf("%d %d\n", 1, i);
			}
		}
	}
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}
