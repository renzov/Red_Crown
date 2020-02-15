#include<cstdio>
#include<map>
using namespace std;
const int MAXN = 40005;

map<int,int> cnt;
int A[MAXN];

void process(){
	int N;
	scanf("%d", &N);
	for ( int i=0; i < N; ++i )
		scanf("%d", A + i);
	
	int res = 0;
	for ( int i=N-1; i >= 0; --i ){
		res += cnt[ A[i] ];
		if ( A[i] != 1 ){
			if ( A[i] == 0 ) cnt[0]++;
			else if ( (A[i] % (A[i]  - 1)) == 0 ) cnt[ A[i]/(A[i] - 1) ]++;
		}
	}
	printf("%d\n", res);
	cnt.clear();
}

int main(){

	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}

