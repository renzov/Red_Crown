#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef pair<int, int> pii;
const int MAXN = 300005;

vector<pii> R;
int A[MAXN];
int B[MAXN];
int f[MAXN];

int main(){
	
	int N;

	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d", A + i );
		B[i] = A[i];
	}
	sort( B, B + N );
	int M = unique( B, B + N ) - B;
	// remap values to 0 ... N - 1
	for ( int i=0; i < N; ++i )
		A[i] = lower_bound( B, B + M, A[i] ) - B;
	
	int l = 0; 
	int r = 0;

	while ( r < N ){
		f[ A[r] ]++;
		if ( f[ A[r] ] == 2 ) { // we need to break
			// clean the frequency vector
			for ( int i=l; i <= r; ++i )
				f[ A[i] ]--;
			//
			R.push_back( pii( l + 1, r + 1 ) );
			l = r + 1;
		}
		r++;
	}

	bool ok = true;
	if ( l < N ){
		if ( R.empty() ){
			ok = false;
		}
		else {
			l = R.back().first - 1;
			r = R.back().second - 1;
			R.back().second = N;	
		}
	}
	
	if ( !ok ) puts("-1");
	else {
		printf("%d\n", (int)R.size() );
		for ( int i=0; i < (int)R.size(); ++i )
			printf("%d %d\n", R[i].first, R[i].second);
	}
	return 0;	
}
