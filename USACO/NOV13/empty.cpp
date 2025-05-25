#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int MAXN = 3000005;

int f[MAXN];
inline int find_set( const int &x ){ return x == f[x]? x:( f[x] = find_set( f[x] ) ); }

int main(){
	int N, K;
	int p, nxt;
	long long X, Y, A, B;

	freopen ("empty.in", "r", stdin);
	freopen ("empty.out", "w", stdout);	

	scanf("%d %d", &N, &K);
	// Initialize the sets
	for ( int i = 0; i < N; ++i )
		f[i] = i;
	
	for ( int i = 0; i < K; ++i ){
		scanf("%lld %lld %lld %lld", &X, &Y, &A, &B);
		for ( int j = 1; j <= Y; ++j ){
			p = (int)((A * j + B) % N);
			for ( int k = 0; k < X; ++k ){
				p = find_set( p );
				nxt = (p + 1) % N;
				f[p] = nxt;
			}
		}
	}
	printf("%d\n", find_set(0));
	return 0;
}
