#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std; 
typedef pair<long long, long long> point;
const int MAXN = 42;

int X[MAXN];
int Y[MAXN];

vector< vector<point> > gen_vectors( const int &b, const int &size ){
	long long x, y;
	int bits;
	vector< vector<point> > res = vector< vector<point> >( size + 1 );
	
	res[0].push_back( point(0LL, 0LL) );

	for ( int mask = 1; mask < (1 << size); ++mask ){
		x = y = 0LL;
		bits = __builtin_popcount( mask );
		for ( int i = 0; i < size; ++i ){
			if ( (mask >> i) & 1 )
				x += X[b + i], y += Y[b + i];
		}
		res[ bits ].push_back( point( x, y ) );
	}
	for ( int i = 0; i <= size; ++i )
		sort( res[i].begin(), res[i].end() );
	return res;
}

int main(){
	int N;
	long long ex, ey;
	scanf("%d %lld %lld", &N, &ex, &ey);
	for ( int i = 0; i < N; ++i )
		scanf("%d %d", X + i, Y + i);

	int n = N >> 1;
	int m = N - n;

	vector< vector<point> > L = gen_vectors( 0, n );
	vector< vector<point> > R = gen_vectors( n, m );
	vector<long long> ans( N + 1, 0LL );

	long long x, y;
	vector<point>::iterator lp, rp;

	for ( int i = 0; i <= m; ++i ){
		for ( int j = 0; j < (int)R[i].size(); ++j ){
			x = ex - R[i][j].first, 
			y = ey - R[i][j].second;
		
			for ( int k = 0; k <= n; ++k ){
				lp = lower_bound( L[k].begin(), L[k].end(), point(x, y) );
				rp = upper_bound( L[k].begin(), L[k].end(), point(x, y) );
				ans[i + k] += distance( lp, rp );
			}

		}
	}
	
	for ( int i = 1; i <= N; ++i )
		printf("%lld\n", ans[i] );
	return 0;
}
