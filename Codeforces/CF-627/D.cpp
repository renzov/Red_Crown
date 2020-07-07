#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 200005;

int pos[MAXN];
int neg[MAXN];
int A[MAXN];
int B[MAXN];

void process(){
	int N;
	int a, b;

	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d", A + i);
	}
	for ( int i=0; i < N; ++i ){
		scanf("%d", B + i);
	}
	for ( int i=0; i < N; ++i ){
		pos[i] = A[i] - B[i];
		neg[i] = -pos[i];
	}

	sort( neg, neg + N );
	long long res = 0;
	int p;
	for ( int i=0; i < N; ++i ){
		p = lower_bound( neg, neg + N, pos[i] ) - neg;
		if ( pos[i] > 0 ) p--;
		res += p;
	}
	res /= 2;
	printf("%lld\n", res);
}

int main(){
	process();
	return 0;
}
