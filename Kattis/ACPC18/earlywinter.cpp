#include<cstdio>
using namespace std;
const int MAXN = 128;
int D[MAXN];

int main(){
	int N, d;
	scanf("%d %d", &N, &d);
	for ( int i=0; i < N; ++i )
		scanf("%d", D + i );

	if ( D[0] <= d ) printf("It hadn't snowed this early in %d years!\n", 0);
	else {
		int i = 0;
		while ( i < N && D[i] > d ) i++;
		if ( i < N ) printf("It hadn't snowed this early in %d years!\n", i);
		else puts("It had never snowed this early!");
	}
	return 0;
}
