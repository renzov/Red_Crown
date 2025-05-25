#include<cstdio>
using namespace std;
const int MAXN = 100005;
long long psum[MAXN] = {0};

int main(){
	int N, Q;
	int L, R;
	int a;

	freopen("sum2.in", "r", stdin);
	freopen("sum2.out", "w", stdout);

	scanf("%d", &N);
	for ( int i = 1; i <= N; ++i ){
		scanf("%d", &a);
		psum[i] = psum[i - 1] + a;
	}

	scanf("%d", &Q);
	while ( Q-- ){
		scanf("%d %d", &L, &R);
		printf("%lld\n", psum[R] - psum[L - 1]);
	} 
	return 0;
}
