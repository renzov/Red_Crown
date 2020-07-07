#include<cstdio>
#include<vector>
#include<cmath>
#include<iterator>
#include<algorithm>
using namespace std;
typedef pair<int,int> pii;
const int MAXN = 50005;
const int SQRT = 224;
int N, Q;
vector<int> A[MAXN];
pii V[SQRT + 5][MAXN];
int K[MAXN];
int main(){
	int x, l, r, m;
	int M = 0;
	scanf("%d %d", &N, &Q);
	for ( int i=0; i < N; ++i ){
		scanf("%d", K + i);
		A[ K[i] ].push_back(i);
	}
	M = *max_element( K, K + N );
	int SQ = sqrt( M ) + 2;
	for ( int i=1; i <= SQ; ++i ){
		for ( int j=0; j < N; ++j )
			V[i][j] = pii( K[j] % i, j );
		sort( V[i], V[i] + N );
	}

	int left, right;
	while ( Q-- ){
		scanf("%d %d %d %d", &l, &r, &x, &m );
		l--, r--;
		if ( m <= SQ ){
			left = lower_bound( V[m], V[m] + N, pii(x, l) ) - V[m];
			right = upper_bound( V[m], V[m] + N, pii(x, r) ) - V[m];
			printf("%d\n", right - left);
		}
		else {
			int res = 0;
			for ( ; x <= M; x += m ){
				res += distance( lower_bound( A[x].begin(), A[x].end(), l ) , upper_bound( A[x].begin(), A[x].end(), r ) );
			}
			printf("%d\n", res);
		}
	}
	return 0;
}
