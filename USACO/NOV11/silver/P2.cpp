#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;
typedef pair<int,int> pii;
const int MAXN = 50005;

map<int,int> active;
pii C[MAXN];
int ID[MAXN];
int N;

int main(){

	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d %d", &C[i].first, &C[i].second);
		ID[ i ] = C[i].second;
	}
	// Get the number of differente ids
	sort( ID, ID + N );
	int M = unique( ID, ID + N ) - ID;
	// sort by position
	sort( C, C + N );
	int last;		// next to last element in the window
	int cnt = 0; 	// number of different elements
	int val;		// number of elements with a given id

	for ( last=0; last < N && cnt < M; ++last ){
		val = active[ C[last].second ]++;
		if ( !val ) cnt++;
	}
	// There is always a solution
	int res = C[last - 1].first - C[0].first;
	// Sliding window
	for ( int i=1; i < N && cnt == M; ++i ){
		val = --active[ C[i-1].second ];
		if ( !val ) cnt--;
		while ( last < N && cnt < M ){
			val = active[ C[last].second ]++;
			if ( !val ) cnt++;
			last++;
		}
		if ( cnt == M ) res = min( res , C[last - 1].first - C[i].first );
	}
	printf("%d\n", res);
	return 0;
}
