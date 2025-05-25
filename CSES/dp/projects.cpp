#include<cstdio>
#include<climits>
#include<set>
#include<algorithm>
using namespace std;

typedef pair<int,int> pii;
typedef pair<int, pii> piii;
typedef pair<int, long long> pil;

const int MAXN = 200005;

piii P[MAXN];

int main(){
	
	int N;
	int a, b, p;

	scanf("%d", &N);
	for ( int i = 0; i < N; ++i ){
		scanf("%d %d %d", &a, &b, &p);
		P[i] = piii( b, pii( a, p ) );
	}
	sort( P, P + N );
	
	set< pil > dp;
	set< pil >::iterator nxt;
	set< pil >::iterator prev;
	long long best; 

	dp.insert( pil( INT_MIN, 0LL ) ); // dummy state
	for ( int i = 0; i < N; ++i ){
		prev = dp.upper_bound( pil( P[i].second.first, LLONG_MIN ) );
		prev--;	// this interval ends before [a_i, b_i] -- always exists because of dummy
		best = P[i].second.second + prev->second;
		prev = dp.upper_bound( pil( P[i].first, LLONG_MIN ) );
		prev--;	// end point is stricly less that [a_i, b_i]
		if ( prev->second >= best ) continue;	// not optimal state - no insert
		nxt = prev;
		nxt++;
		while ( nxt != dp.end() && best >= nxt->second ){
			prev = nxt++;
			dp.erase( prev );
		}
		if ( nxt == dp.end() || nxt->first > P[i].first )
			dp.insert( pil( P[i].first, best ) );
	}
	printf("%lld\n", dp.rbegin()->second );
	return 0;
}
