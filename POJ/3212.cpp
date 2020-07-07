#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
typedef pair<int, int> pii;
const int MAXN = 100005;
pii X[MAXN];
pii Y[MAXN];
long long res[MAXN];

void computeDist( pii P[], const int &N ){
	long long sumR = 0;
	long long sumL = 0;
	int idx;
	long long d = 0;

	for ( int i=1; i < N; ++i )
		sumR += P[i].first;
	for ( int i=0; i < N; ++i ){
		idx = P[i].second;
		d = (1LL * i * P[i].first - sumL) + (sumR - 1LL * (N - 1 - i) * P[i].first);
		res[idx] += d;
		sumL += P[i].first;
		if ( i + 1 < N )
			sumR -= P[i + 1].first;
	}
}

int main(){
	int N;
	int x, y;

	scanf("%d", &N);

	for ( int i=0; i < N; ++i ){
		scanf("%d %d", &x, &y);
		X[i].first = (x + y); X[i].second = i;
		Y[i].first = (x - y); Y[i].second = i; 
	}
	sort( X, X + N );
	sort( Y, Y + N );
	// Compute for each dimension
	computeDist( X, N );
	computeDist( Y, N );
	printf("%lld\n", *min_element( res, res + N ) >> 1);
	return 0;
}
