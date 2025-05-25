#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 100005;
int H[MAXN];

int main(){
	int N;
	long long A, B;

	scanf("%d %lld %lld", &N, &A, &B);
	for ( int i=0; i < N; ++i )
		scanf("%d", H + i);

	sort( H, H + N );
	
	long long res = 0;
	long long act, nxt;
	
	for ( int i=1; i < N; ++i )
		res += B * ( H[i] - H[0] );
	
	act = res;
	for ( int i=1; i < N; ++i ){
		nxt = act;
		// invariant: at the beginning of each iteration "act" is the cost of H[i - 1] being the host
		nxt -= (B * ( H[i] - H[i - 1] ) * (N - i));	
		nxt += (A * ( H[i] - H[i - 1] ) * i);
		res = min( res, nxt );
		act = nxt;
	}
	printf("%lld\n", res);
	return 0;
}
