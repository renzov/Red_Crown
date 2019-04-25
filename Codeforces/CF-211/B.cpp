#include<cstdio>
#include<climits>
using namespace std;
const int MAXN = 200000;
int S[MAXN];

int main(){
	int h;
	int N;
	int K;
	scanf("%d %d", &N, &K);
	for ( int i=1; i <= N; ++i ){
		scanf("%d", &h);
		S[i] = S[i - 1] + h;
	}
	int res = INT_MAX;
	int best = -1;
	for ( int i=1; i <= (N - K + 1); ++i ){
		if ( res > (S[i + K - 1] - S[i - 1]) ){
			res = S[i + K - 1] - S[i - 1];
			best = i; 
		}
	}
	printf("%d\n", best);
	return 0;
}
