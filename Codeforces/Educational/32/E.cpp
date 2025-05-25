#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN = 36;

int M;
int A[MAXN];

vector<int> gen_all_sums( const int &b, const int &size ){
	vector<int> V;

	V.push_back( 0 );

	for ( int mask = 1; mask < (1 << size); ++mask ){
		int val = 0LL;
		for ( int i = 0; i < size; ++i )
			if ( (mask >> i)&1 )
				val = ( val + A[b + i] ) % M;
		V.push_back( val );
	}
	sort( V.begin(), V.end() );
	return V;
}

int main(){
	int N;

	scanf("%d %d", &N, &M);
	for ( int i=0; i < N; ++i )
		scanf("%d", A + i );
	
	int n = N >> 1;
	int m = N - n;

	vector<int> L = gen_all_sums( 0, n );
	vector<int> R = gen_all_sums( n, m );
	
	int res = 0;

	for ( int i = 0; i < (int)R.size(); ++i ){
		vector<int>::iterator p = lower_bound( L.begin(), L.end(), M - R[i] );
		if ( p != L.begin() ){
			p--;
			res = max( res, R[i] + *p );
		}
	}
	printf("%d\n", res );
	return 0;
}
