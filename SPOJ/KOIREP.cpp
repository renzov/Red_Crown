#include<cstdio>
#include<algorithm>
#include<climits>
using namespace std;
const int MAXN = 1024;
int C[MAXN * MAXN];
int A[MAXN * MAXN];
int ord[ MAXN * MAXN ];
int f[ MAXN ];

bool cmp( const int &i, const int &j ){
	return A[i] < A[j];
}

int main(){
	int N, M;
	int a;
	scanf("%d %d", &N, &M);
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < M; ++j ){
			scanf("%d", &a );
			C[ i*M + j ] = i;
			A[ i*M + j ] = a;
		}
	for ( int i=0; i < N*M; ++i )
		ord[i] = i;

	sort( ord, ord + N*M, cmp );

	int l = 0;		// left pointer of the window
	int r = 0;		// right pointer of the window --- [l, r)
	int c;
	int cnt = 0;	// active classes in the window	
	int res = INT_MAX;
	int idx;
	while ( r < N*M ){
		while ( cnt < N && r < N*M ){
			idx = ord[r];
			c = C[ idx ];
			f[c]++;
			if ( f[c] == 1 ) cnt++;
			r++;
		}
		if ( cnt == N ){
			res = min( res, A[ ord[r - 1] ] - A[ ord[l] ] );
		}
		// Remove the one in the left
		idx = ord[l];
		c = C[idx];
		f[c]--;
		if ( f[c] == 0 ) cnt--;
		l++;
	}
	printf("%d\n", res);
	return 0;
}
