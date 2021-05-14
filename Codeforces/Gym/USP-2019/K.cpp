#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 1000005;
long long A[MAXN];

int main(){
	int N;

	scanf("%d", &N);
	for ( int i=0; i < N; ++i )
		scanf("%lld", A + i);
	sort( A, A + N );

	long long last = 0;
	bool found = false;
	for ( int i=0; i < N && ((last + 1) >= A[i]); ++i ){
		last += A[i];
	}
	printf("%lld\n", last + 1);
	return 0;
}
