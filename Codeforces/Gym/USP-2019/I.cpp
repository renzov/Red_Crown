#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;
const int MAXN = 100005;
pair<int,int> A[MAXN];

int main(){
	int N;
	int p, f;

	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d %d", &p, &f);
		A[i].first = -f;
		A[i].second = p;
	}
	sort( A, A + N );
	reverse( A, A + N );
	
	long long res = LLONG_MIN;
	long long sp = 0;
	for ( int i=0; i < N; ++i ){
		sp += A[i].second;
		res = max( res, sp + A[i].first );
	}
	printf("%lld\n", res);
	return 0;
}
