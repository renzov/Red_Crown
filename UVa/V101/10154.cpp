#include<cstdio> 
#include<algorithm>
#include<climits>
using namespace std;

typedef pair<int,int> pii;
const int MAXN = 6000;

pii T[MAXN];
int totalW[MAXN];
 
int main(){
	int N = 0;
	int S, W;
	
	while ( scanf("%d %d", &W, &S) != EOF ){
		T[N++] = pii( S, W );
	}
	
	sort( T, T + N );
	fill(totalW, totalW + N, INT_MAX );
	totalW[0] = 0;
	int size = 0;
	
	for ( int i=0; i < N; i++ ){
		// Test the i-th turtle
		S = T[i].first, W = T[i].second;
		for ( int j=size; j >= 0; --j ){
			if ( S >= totalW[j] + W && W + totalW[j] < totalW[j + 1] ){
				totalW[j + 1] = totalW[j] + W;
				size = max( size, j + 1 );
			} 
		}		
	}
	printf("%d\n", size);
	return 0;
}
