#include<cstdio>
using namespace std;
const int MAXN = 100005;
int S[3][MAXN];

inline int getSum( const int &v, const int &l, const int &r ){
	return S[v][r] - S[v][l - 1];
}

int main(){
	freopen("bcount.in", "r", stdin );
	freopen("bcount.out", "w", stdout );

	int N, Q, v;

	scanf("%d %d", &N, &Q);
	for ( int i = 1; i <= N; ++i ){
		scanf("%d", &v);
		v--;
		S[v][i]++;
	}
	for ( int v = 0; v < 3; ++v )
		for ( int i = 1; i <= N; ++i )
			S[v][i] += S[v][i - 1];

	int l, r;
	while ( Q-- ){
		scanf("%d %d", &l, &r);
		printf("%d %d %d\n", getSum( 0, l, r ), getSum(1, l, r), getSum(2, l, r));
	}
	return 0;
}
