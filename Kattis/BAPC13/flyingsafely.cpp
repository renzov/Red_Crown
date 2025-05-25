#include<cstdio>
using namespace std;

void process(){
	int N, M;
	int a, b;
	scanf("%d %d", &N, &M );
	while ( M-- ){
		scanf("%d %d", &a, &b);
	}
	printf("%d\n", N - 1);
}

int main(){
	int t;
	scanf("%d", &t);
	while ( t-- )
		process();
	return 0;
}
