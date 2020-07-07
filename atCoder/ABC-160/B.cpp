#include<cstdio>
using namespace std;

int main(){
	int N;
	scanf("%d", &N);
	int a = N / 500;
	N %= 500;
	int b = N / 5;
	printf("%d\n", 1000*a + 5*b);
	return 0;
}
