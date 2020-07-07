#include<cstdio>
using namespace std;

const int MAXN = 200005;
long long A[MAXN];

int main(){
	int N, M;
	long long b;
	scanf("%d %d", &N, &M);
	for ( int i=0; i < N; ++i ){
		scanf("%lld", A + i);
	}
	long long sofar = 0;
	int cur = 0;
	for ( int i=0; i < M; ++i ){
		scanf("%lld", &b);
		b -= sofar;
		while ( b > A[cur] ){
			sofar += A[cur];
			b -= A[cur];
			cur++;			
		}
		printf("%d %lld\n", cur + 1, b);
	}
	return 0;
}
