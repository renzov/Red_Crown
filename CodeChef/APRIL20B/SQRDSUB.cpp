#include<cstdio>
#include<map>
using namespace std;

map<int,int> cnt;

void process(){
	int N, A;
	int sum = 0;
	int e;
	long long bad = 0;

	scanf("%d", &N);
	cnt.clear();
	cnt[0] = 1;
	for ( int i=0; i < N; ++i ){
		scanf("%d", &A);
		if ( A < 0 ) A *= -1;
		if ( A == 0 ){
			cnt.clear();
			cnt[0] = 1;
			sum = 0;
		}
		else {
			e = 0;
			while ( !( A & 1 ) ){
				A >>= 1;
				e++;
			}
			sum += e;
			bad += cnt[ sum - 1 ];
			cnt[ sum ]++;
		}

	}
	long long total = 1LL * N * ( N + 1 ) / 2;
	printf("%lld\n", total - bad );
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- ) 
		process();
	return 0;
}
