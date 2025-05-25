#include<cstdio>
#include<algorithm>
using namespace std;

int main(){
	int N;
	long long L, R;
	scanf("%d", &N);

	while ( N-- ){
		scanf("%lld %lld", &L, &R);
		R++;
		printf("%.12f\n", (double)1/L - (double)1/R);
	}
	return 0;
}
