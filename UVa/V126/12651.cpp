#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 100005;

int D[2*MAXN];
int E[MAXN];	// E[i] = j iff D[i] + ... + D[j - 1] = len, otherwise E[i] = -1

int main(){
	int N;
	int L;
	int res;

	while ( scanf("%d", &N) == 1 ){
		L = 0;
		for ( int i =0; i < N; ++i ){
			scanf("%d", D + i );
			L += D[i];
			D[i + N] = D[i];
		}
		if ( L % 3 ){
			puts("0");
		}
		else {
			L /= 3;
			res = 0;
			// First, for each i, we calculate if there is a segment beginning in i of lenth L
			int j = 0;
			int sum = 0;
			for ( int i = 0; i < N; ++i ){
				while ( sum + D[j] <= L ){
					sum += D[j];
					j++;
				}
				if ( sum == L ) 
					E[i] = j % N;
				else 
					E[i] = -1;
				sum -= D[i];
			}
			// Now, we count the triangles
			for ( int i = 0; i < N; ++i ){
				if ( E[i] >= 0 && E[ E[i] ] >= 0 )
					res++;
			}
			// We have count each triangle 3 times
			res /= 3;
			printf("%d\n", res);
		}
	}
	return 0;
}
