#include<cstdio>
#include<cstdlib>
using namespace std;
const int MAXN = 32;

int pos[MAXN][MAXN];

int main(){
	int N, M;
	int idx;
	
	freopen ("gymnastics.in", "r", stdin);
	freopen ("gymnastics.out", "w", stdout);
	
	scanf("%d %d", &M, &N);

	for ( int j=0; j < M; ++j )
		for ( int i=0; i < N; ++i ){
			scanf("%d", &idx);
			idx--;
			pos[idx][j] = i;
		}

	int res = 0;
	int cnt;
	for ( int i=0; i < N; ++i )
		for ( int j=i + 1; j < N; ++j ){
			cnt = 0;
			for ( int k=0; k < M; ++k )
				if ( pos[i][k] < pos[j][k] )
					cnt++;
			if ( cnt == M || cnt == 0 ) res++;
		}
	printf("%d\n", res);
	return 0;
}
