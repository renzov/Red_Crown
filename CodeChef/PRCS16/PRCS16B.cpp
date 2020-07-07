#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;
typedef pair<int,int> pii;
const int MAXN = 1000006;

pii A[MAXN];
int P[MAXN];
int N;

inline int dist( const int &A, const int &B ){
	return ( A <= B )? (B - A):(B - A + N);
}

int main(){
	int M;
	int v;

	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d", &v);
		A[i] = pii( v, i );
	}
	
	sort( A, A + N );
	int res = INT_MAX;
	int last, tmp;

	for ( int i=0; i < N;  ){
		v = A[i].first;
		M = 0;
		
		for ( ; i < N && A[i].first == v; ++i )
			P[M++] = A[i].second;
		
		last = P[M - 1];
		tmp = 0;
		for ( int j=0; j < M; ++j ){
			v = P[j];
			tmp = max( tmp, dist( last , v ) - 1 );
			last = v;
		}
		if ( M == 1 ){
			tmp = N - 1;
		}
		res = min( res, N + tmp );
	}
	printf("%d\n", res);
	return 0;
}
