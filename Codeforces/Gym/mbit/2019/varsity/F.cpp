#include<cstdio>
using namespace std;
const int MAXN = 1000005;

int P[MAXN];
int S[MAXN];
int idx[MAXN];
bool vis[MAXN] = {0};
int N, K;
int M;

int main(){

	scanf("%d %d", &N, &K);
	for ( int i=0; i < N; ++i ){
		scanf("%d", P + i );
		P[i]--;
	}

	int act = 0;
	int nxt;
	M = 1;
	S[0] = 0;
	vis[0] = true;
	idx[ 0 ] = 0;

	while ( !vis[ P[act] ] && K ){
		act = P[act];		
		idx[ act ] = M;
		S[M++] = act;
		vis[act] = true;
		K--;
	}
	if ( K == 0 ) printf("%d\n", act + 1);
	else { // K > 0 && cycle found
		K--;
		act = P[act]; // begin of cycle
		int L = M - idx[act];	// length of cycle
		K = K % L;
		printf("%d\n", S[ idx[act] + K ] + 1 );
	}
	return 0;
}
