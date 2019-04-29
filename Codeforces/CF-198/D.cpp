#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;
const int MAXN = 100005;
int ord[MAXN];

int main(){
	int a;
	int N;
	int M = 0;
	int pos;

	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d", &a);
		if ( M == 0 || ord[M-1] < a ) ord[M++] = a;
		else if ( ord[0] > a ) ord[0] = a;
		else {  // ord[0] < a && ord[M-1] > a 
			pos = lower_bound( ord, ord + M, a ) - ord;
			ord[pos] = a;
		}
	}
	printf("%d\n", M);
	return 0;
}
