#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const int MAXN = 256;
int f[MAXN];
int A[MAXN];

void process(){
	int N;
	scanf("%d", &N);
	fill( f, f + (N  + 1), 0 );
	f[0] = 1;
	A[0] = 0;
	for ( int i=0; i < N-1; ++i ){
		if ( f[ A[i] ] == 1 ){
			A[i + 1] = 0;
			f[ 0 ]++;
		}
		else {
			for ( int j=i - 1; j >= 0; --j )
				if ( A[j] == A[i] ){
					A[ i + 1 ] = i - j;
					f[ i - j ]++;
					break;
				}
		}
	}
	printf("%d\n", f[ A[N - 1] ]);
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- ) process();
	return 0;
}
