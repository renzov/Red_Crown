#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 128;

int A[MAXN];
int LA[MAXN];
int B[MAXN];
int LB[MAXN];

int main(){
	freopen ("speeding.in", "r", stdin );
	freopen ("speeding.out", "w", stdout );
	

	int N, M;
	int x;

	scanf("%d %d", &N, &M);
	A[0] = 0;
	for ( int i=1; i <= N; ++i ){
		scanf("%d %d", &x, LA + i );
		A[i] = A[i - 1] + x;
	}
	B[0] = 0;
	for ( int i=1; i <= M; ++i ){
		scanf("%d %d", &x, LB + i);
		B[i] = B[i - 1] + x;
	}

	int l = 0;
	int r = 0;
	int p = 0;
	int res = 0;

	while ( l <= N && r <= M ){
		if ( A[l] < B[r] ){
			p = A[l];
		}
		else {
			p = B[r];
		}
		res = max( res, LB[r] - LA[l] );
		if ( p == A[l] ) l++;
		if ( p == B[r] ) r++;
	}
	printf("%d\n", res);
	return 0;
}
