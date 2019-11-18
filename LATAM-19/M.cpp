#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 1024;
int H[MAXN];
int L[MAXN];
int main(){
	int N, X;

	scanf("%d %d", &N, &X);
	for ( int i=0; i < N; ++i )
		scanf("%d", H + i);
	L[N - 1] = 1;
	for ( int i=N - 2; i >= 0; --i )
		if ( H[i + 1] - H[i] <= X )
			L[i] = L[i + 1] + 1;
		else 
			L[i] = 1;
	printf("%d\n", *max_element(L, L + N));
	return 0;
}
