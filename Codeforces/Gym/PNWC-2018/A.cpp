#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 1024;
char A[MAXN], B[MAXN];

int main(){
	int K;
	int E = 0;
	int D = 0;
	scanf("%d %s %s", &K, A, B);
	
	for ( int i=0; A[i]; ++i )
		if ( A[i] == B[i] ) E++;
		else D++;
	
	if ( E >= K ) printf("%d\n", D + K );
	else printf("%d\n", D - (K - E) + E);
	return 0;
}
