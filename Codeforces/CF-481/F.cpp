#include<cstdio>
#include<algorithm>
#include<vector>
#include <iterator>     // std::distance
using namespace std;
const int MAXN = 200005;

int N, M;
vector<int> B[MAXN];
int S[MAXN];
int ord[MAXN];

int main(){

	scanf("%d %d", &N, &M);
	for ( int i=0; i < N; ++i ){
		scanf("%d", S + i);
		ord[i] = S[i];
	}
	
	int u, v;
	while ( M-- ){
		scanf("%d %d", &u, &v);
		u--, v--;
		B[u].push_back( S[v] );
		B[v].push_back( S[u] );
	}

	sort( ord, ord + N );
	for ( int i=0; i < N; ++i )
		sort( B[i].begin(), B[i].end() );
	
	for ( int i=0; i < N; ++i ){
		int total = lower_bound( ord, ord + N, S[i] ) - ord;
		total -= distance( B[i].begin(), lower_bound( B[i].begin(), B[i].end(), S[i] ) );
		if (i) putchar(' ');
		printf("%d", total);
	}
	puts("");
	return 0;
}
