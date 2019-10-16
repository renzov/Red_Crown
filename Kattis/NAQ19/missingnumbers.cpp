#include<cstdio>
using namespace std;

int f[256];

int main(){
	int N;
	int x;

	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d", &x);
		f[x]++;
	}
	int cnt = 0;
	for ( int i=1; i <= x; ++i ){
		if ( !f[i] ) printf("%d\n", i), cnt++;
	}
	if ( !cnt ) puts("good job");
	return 0;
}
