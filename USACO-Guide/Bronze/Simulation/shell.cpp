#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 128;
int A[MAXN];
int B[MAXN];
int G[MAXN];
bool in[4];
int N;

int guess( const int &x ){
	in[1] = in[2] = in[3] = false;
	in[ x ] = true;

	int res = 0;
	for ( int i=0; i < N; ++i ){
		swap( in[ A[i] ], in[ B[i] ] );
		if ( in[ G[i] ] ) res++;
	}
	return res;
}

int main(){
	freopen ("shell.in", "r", stdin);
	freopen ("shell.out", "w", stdout);
	
	scanf("%d", &N);
	for ( int i=0; i < N; ++i )
		scanf("%d %d %d", A + i, B + i, G + i);

	int res = guess(1);
	res = max( res, guess(2) );
	res = max( res, guess(3) );
	printf("%d\n", res);
	return 0;
}
