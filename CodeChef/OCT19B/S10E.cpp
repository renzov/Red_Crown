#include<cstdio>
using namespace std;
const int MAXN = 128;
int A[MAXN];

void process(){
	int N;
	bool ok;
	int res = 0;
	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d", A+i);
		ok = true;
		for ( int j=i-1; j >= 0 && j >= i - 5 && ok; --j )
			ok &= ( A[i] < A[j] );
		if ( ok ) res++;
	}
	printf("%d\n", res);
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}
