#include<cstdio>
using namespace std;

int N;
int cnt[25];
int V[25];

void process(){
	int t;
	
	for ( int i=0; i < N; ++i ){
		scanf("%d", &t);
		cnt[ t + 11 ]++;	// remap t to t + 11 and work with 0 ... 23
	}

	int M = 0;
	int res = 0;
	// Just consider the times where there are an odd number of persons
	for ( int i=0; i < 24; ++i )
		if ( cnt[i] & 1 )
			V[M++] = i;
	// In an optimal solution there is no "crossings" in the pairing
	if ( M > 0 ){
		// Pair greedily forward
		int cost = 0;
		for ( int i=0; i < M; i += 2 )
			cost += ( V[i + 1] - V[i] );
		res = cost;
		// Now pair greedily backward
		V[M] = V[0] + 24;
		cost = 0;
		for ( int i=M; i > 0; i -= 2 )
			cost += ( V[i] - V[i - 1] );
	
		if ( res > cost )
			res = cost;
	}
	printf("%d\n", res);
}

int main(){
	while ( scanf("%d", &N) == 1 ){
		process();
		for ( int i=0; i < 24; ++i )
			cnt[i] = 0;
	}
	return 0;
}
