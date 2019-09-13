#include<cstdio>
#include<queue>
using namespace std;
typedef pair<int,int> pii;
const int MAXN = 1000005;
deque< pii > minQ;
deque< pii > maxQ;
int minR[ MAXN ];
int maxR[ MAXN ];
int N, K;

int main(){
	int i, x;
	
	scanf("%d %d", &N, &K);
	for ( i=0; i < K; ++i ){
		scanf("%d", &x);
		// Insert in minQ
		while ( !minQ.empty() && minQ.back().first >= x ) minQ.pop_back();
		minQ.push_back( pii( x, i ) );
		// Insert in maxQ
		while ( !maxQ.empty() && maxQ.back().first <= x ) maxQ.pop_back(); 
		maxQ.push_back( pii( x, i ) );

	}
	
	for ( ; i < N; ++i ){
		
		minR[i - K] = minQ.front().first;
		maxR[i - K] = maxQ.front().first;	
		while ( !minQ.empty() && minQ.front().second <= i - K ) minQ.pop_front();
		while ( !maxQ.empty() && maxQ.front().second <= i - K ) maxQ.pop_front();
		scanf("%d", &x);
		// Insert in minQ
		while ( !minQ.empty() && minQ.back().first >= x ) minQ.pop_back();
		minQ.push_back( pii( x, i ) );
		// Insert in maxQ
		while ( !maxQ.empty() && maxQ.back().first <= x ) maxQ.pop_back();
		maxQ.push_back( pii( x, i ) );
	}
	minR[i - K] = minQ.front().first;
	maxR[i - K] = maxQ.front().first;	
	// Print the answers
	printf("%d", minR[0]);
	for ( int i=1; i <= N - K; ++i ){
		printf(" %d", minR[i]);
	}
	puts("");
	printf("%d", maxR[0]);
	for ( int i=1; i <= N - K; ++i ){
		printf(" %d", maxR[i]);
	}
	puts("");
	return 0;
}
