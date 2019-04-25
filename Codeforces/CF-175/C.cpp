#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 3*100005;
int A[MAXN];

int main(){
	
	int N;
	scanf("%d", &N);
	for ( int i=0; i < N; ++i ) scanf("%d", A + i);
	sort(A, A + N);
	long long res = 0;
	for ( long long i=1; i <= N; ++i )
		res += llabs(A[i-1] - i);
	printf("%I64d\n", res);
	return 0;
}
