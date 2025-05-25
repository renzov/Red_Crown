#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 1 << 10;

int A[MAXN];

int main(){
	int N, Q;
	int L, R;

	freopen("stupid_rmq.in", "r", stdin);
	freopen("stupid_rmq.out", "w", stdout);

	scanf("%d", &N);
	for ( int i = 0; i < N; ++i )
		scanf("%d", A + i);
		
	scanf("%d", &Q);
	while ( Q-- ){
		scanf("%d %d", &L, &R);
		L--;
		printf("%d\n", *min_element( A + L, A + R ) );
	}
	return 0;
}
