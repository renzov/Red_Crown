#include<cstdio>
#include<algorithm>
using namespace std;
typedef pair<int,int> pii;
const int MAXN = 100005;

long long A[MAXN];
long long B[MAXN];

int main(){
	int N;	
	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%lld", A + i); 
		B[i] = A[i];
	}
	sort( B, B + N );
	
	int res = 0;
	
	for ( int i=0; i < N; ++i )
		if (A[i] == B[i] ) res++;

	printf("%d\n", res);
	return 0;
}
