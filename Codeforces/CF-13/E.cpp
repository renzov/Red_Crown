#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int MAXN = 100005;

int A[MAXN];
int block[MAXN];
int nxt[MAXN];
int cnt[MAXN];
int ending[MAXN];

int main(){
	int N, Q;
	int p;

	scanf("%d %d", &N, &Q);
	for ( int i=0; i < N; ++i )
		scanf("%d", A + i);

	int len = (int)sqrt( (double)N ) + 1;
	// Calculate the necessay info
	for ( int i=0, last; i < N; i+= len ){
		last = min( i + len, N ) - 1;
		for ( int j=last; j >= i; --j ){
			block[j] = i;
			p = min( N, j + A[ j ]);	
			if ( p <= last ){	// in the same block
				cnt[ j ] = cnt[p] + 1;
				nxt[ j ] = nxt[p];
				ending[ j ] = ending[p];
			}
			else {
				cnt[ j ] = 1;
				nxt[ j ] = p;
				ending[ j ] = j;
			}
		}
	}

	int t, a, np;
	int prev;
	int res;

	while ( Q-- ){
		scanf("%d", &t);
		if ( t ){
			scanf("%d", &p);
			p--;
			res = 0;
			while ( p < N ){
				prev = p;
				res += cnt[p];
				p = nxt[p];
			}
			printf("%d %d\n", ending[prev] + 1, res);
		}
		else{
			scanf("%d %d", &p, &a);
			p--;
			A[p] = a;
			for ( int i=p; i >= 0 && block[i] == block[p]; --i ){	// At most sqrt(N) elements
				np = min(i + A[i], N);
				if ( np == N || block[np] != block[i] ){
					cnt[i] = 1, nxt[i] = np, ending[i] = i;
				}
				else {
					cnt[i] = cnt[np] + 1, nxt[i] = nxt[np], ending[i] = ending[np];
				}
			}
		}
	}
	return 0;
}
