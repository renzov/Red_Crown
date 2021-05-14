#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 1000005;
int A[MAXN];
int X;

void process(){
	int N;

	X *= 10000000;

	scanf("%d", &N);
	for ( int i=0; i < N; ++i )
		scanf("%d", A + i);
	sort( A, A + N );

	int l = 0;
	int r = N - 1;

	while ( l < r ){
		while ( l < r && A[l] + A[r] > X ) r--;
		if ( l < r && A[l] + A[r] == X ){
			printf("yes %d %d\n", A[l], A[r]);
			return;
		}
		else { 
			l++;
		}
	}
	puts("danger");
}

int main(){
	while ( scanf("%d", &X) == 1 )
		process();
	return 0;
}
