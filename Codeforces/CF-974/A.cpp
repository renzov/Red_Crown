#include<cstdio>
using namespace std;

void process(){
	int N, K;

	scanf("%d %d", &N, &K);
	int res = 0;
	int a;
	int gold = 0;
	while ( N-- ){
		scanf("%d", &a);
		if ( a >= K ) gold += a;
		else if ( a == 0 && gold ){
			gold--;
			res++;
		}
	}
	printf("%d\n", res);
}

int main(){
	int t;

	scanf("%d", &t);
	while (t--)
		process();
	return 0;
}
