// Greedy interval scheduling problem
#include<cstdio>
#include<algorithm>
using namespace std;
typedef pair<int, int> pii;

const int MAXN = 100005;
pii E[MAXN];

int main(){
	
	int N;

	scanf("%d", &N);
	for ( int i = 0; i < N; ++i )
		scanf("%d %d", &E[i].second, &E[i].first);

	sort( E, E + N );

	int res = 0;
	int last = -1;
	
	for ( int i = 0; i < N; i++ ){
		if ( last < E[i].second ){
			last = E[i].first;
			res++;
		}
	}
	printf("%d\n", res);
	return 0;
}
