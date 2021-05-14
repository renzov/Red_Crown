#include<cstdio>
using namespace std;

void process(){
	int N, M;
	scanf("%d %d", &N, &M);
	if ( N == 1 ) puts("0");
	else if ( N == 2 ) printf("%d\n", M);
	else printf("%d\n", 2*M + N - 3 );
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- ) process();
	return 0;
}
