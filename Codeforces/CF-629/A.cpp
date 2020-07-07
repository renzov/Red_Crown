#include<cstdio>
using namespace std;

void process(){
	int A, B;
	scanf("%d %d", &A, &B);
	if ( A % B == 0 )
		puts("0");
	else if ( A > B )
		printf("%d\n", B - (A % B));
	else 
		printf("%d\n", B - A);
}

int main(){

	int runs;
	scanf("%d", &runs);
	while ( runs-- ) process();

	return 0;
}
