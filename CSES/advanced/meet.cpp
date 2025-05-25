#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

const int MAXN = 45;

int N, X;
int A[MAXN];

vector<long long> all_subs( const int &b, const int &size ){
	vector<long long> V;
	V.push_back( 0LL );

	for ( int mask = 1; mask < (1 << size); ++mask ){
		long long val = 0LL;
		for ( int i = 0; i < size; ++i )
			if ( (mask >> i)&1 )
				val += A[b + i];
		V.push_back( val );
	}
	sort( V.begin(), V.end() );
	return V;
}

int main(){

	scanf("%d %d", &N, &X);
	for ( int i = 0; i < N; i++ )
		scanf("%d", A + i );

	int n = N >> 1;
	int m = N - n;

	vector<long long> L = all_subs( 0, n );
	vector<long long> R = all_subs( n, m );

	long long res = 0LL;
	vector<long long>::iterator lp, rp;

	for ( int i = 0; i < (int)R.size(); ++i ){
		lp = lower_bound( L.begin(), L.end(), X - R[i] );
		rp = upper_bound( L.begin(), L.end(), X - R[i] );
		res += distance( lp, rp );
	}
	printf("%lld\n", res );
	return 0;
}
