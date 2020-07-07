#include<cstdio>
#include<algorithm>
using namespace std;
typedef pair<int, long long> pii;

const int MAXN = 128;
pii A[MAXN];

int coef3( long long x ){
	int res = 0;
	while ( !(x % 3) )
		x /= 3, res++;
	return res;
}

int main(){
	int N;
	long long x;
	scanf("%d", &N);

	for ( int i=0; i < N; ++i ){
		scanf("%I64d", &x);
		A[i] = pii( -coef3(x), x );
	}
	sort( A, A + N );
	for ( int i=0; i < N; ++i ){
		if (i) putchar(' ');
		printf("%I64d", A[i].second);
	}
	puts("");
	return 0;
}
