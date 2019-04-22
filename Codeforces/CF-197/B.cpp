#include<cstdio>
#include<algorithm>
using namespace std;

int main(){
	int a;
	int N, M;
	int p = 1;
	long long res = 0;

	scanf("%d %d", &N, &M);
	
	while (M--){
		scanf("%d", &a);
		if ( a >= p ) res += (a - p);
		else res += (a - p  + N);
		p = a;
	}
	printf("%I64d\n", res);
	return 0;
}
