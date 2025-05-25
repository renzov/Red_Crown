#include<cstdio>
using namespace std;

int main(){
	int N;

	scanf("%d", &N);

	long long s;
	long long prev;

	scanf("%lld", &s);
	prev = s;

	printf("%lld", prev);
	
	for ( int i = 1; i < N; ++i ){
		scanf("%lld", &s);
		printf(" %lld", s - prev);
		prev = s;
	}
	puts("");
	return 0;
}
