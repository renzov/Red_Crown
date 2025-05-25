#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef pair<int, int> pii;
const int MAXN = 200005;

pii A[MAXN];

int main(){
	int N;
	int h, t;

	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d %d", &t, &h);
		A[i].second = t, A[i].first = h;
	}
	sort( A, A + N );
	
	long long sum = 0;
	priority_queue<int> q;
	
	for ( int i=0; i < N; ++i ){
		q.push( A[i].second );
		sum += A[i].second;
		while ( sum > A[i].first ){
			sum -= q.top();
			q.pop();
		}
	}
	printf("%d\n", (int)q.size());
	return 0;
}
