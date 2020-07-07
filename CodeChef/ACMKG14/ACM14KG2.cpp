#include<cstdio>
using namespace std;

void process(){
	int a, N, M;
	scanf("%d %d %d", &N, &a, &M);
	a--;
	a += M;
	a %= N;
	printf("%d\n", a + 1);
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}
