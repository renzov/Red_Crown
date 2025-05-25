#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN = 100005;
const int C = 21563;
const int MOD = 16714589;
int A[MAXN];
int lg[MAXN];

int main(){
	int N, Q;

	freopen("sparse.in", "r", stdin);
	freopen("sparse.out", "w", stdout);

	scanf("%d %d %d", &N, &Q, A);
	for ( int i = 1; i < N; ++i )
		A[i] = (23 * A[i - 1] + C) % MOD;
	
	int log;
	for ( log = 0; (1 << log) <= N; ++log );
	log--;

	lg[1] = 0, lg[2] = 1;
	for ( int i = 3; i <= N; ++i )
		lg[i] = lg[i >> 1] + 1;

	vector< vector<int> > S( log + 1, vector<int>(N,0) );
	for ( int j = 0; j < N; ++j )
		S[0][j] = A[j];
	for ( int i = 1; i <= log; ++i )
		for ( int j = 0; j + (1 << i) <= N; ++j )
			S[i][j] = min( S[i - 1][j], S[i - 1][j + (1 << (i - 1))] );

	int l, r, idx, ans;
	int L, R;
	scanf("%d %d", &l, &r);
	for ( int i = 1; i <= Q; ++i ){
		L = min(l, r);
		R = max(l, r);
		idx = lg[R - L + 1];	
		ans = min( S[idx][L - 1], S[idx][ R - (1 << idx) ] );
		if ( i < Q ){
			l = ( 17 * l + 751 + ans + 2 * i ) % N + 1;
			r = ( 13 * r + 593 + ans + 5 * i ) % N + 1;
		}
	}
	printf("%d %d %d\n", l, r, ans);
	return 0;
}
