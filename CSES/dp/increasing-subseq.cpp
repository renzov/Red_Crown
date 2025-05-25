#include<cstdio>
#include<climits>
#include<set>
#include<algorithm>
using namespace std;
typedef pair<int,int> pii;

int main(){
	int N, X; 
	int ans = 0, len;

	scanf("%d", &N);
	set<pii> dp;
	set<pii>::iterator nxt;

	for ( int i = 0; i < N; ++i ){
		scanf("%d", &X);
		nxt = dp.upper_bound( pii( X, INT_MIN ) );
		if ( nxt == dp.end() ){
			len = (int)dp.size() + 1;
			dp.insert( pii( X, len ) );
			ans = len;
		}
		else {
			if ( nxt->first == X ) continue;
			len = nxt->second;
			dp.erase( nxt );
			dp.insert( pii( X, len ) );
		}
	}
	printf("%d\n", ans);
	return 0;
}
