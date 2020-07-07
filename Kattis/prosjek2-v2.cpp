#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 300005;
int Y[MAXN];
int idx[MAXN];

inline long long area2( const int &X0, const int &Y0, const int &X1, const int &Y1, const int &X2, const int &Y2 ){
	return 1LL*(X1 - X0 )*(Y2 - Y0) - 1LL*(X2 - X0)*(Y1 - Y0); 
}

int main(){	
	int N, K, A;

	scanf("%d %d", &N, &K);
	Y[0] = 0;
	for ( int i=1; i <= N; ++i ){
		scanf("%d", &A);
		Y[i] = Y[i - 1] + A;
		printf("Y[%d] = %d\n", i, Y[i] );
	}


	int size = 2;	
	idx[0] = 0, idx[1] = 1;
	// Find the convex hull
	for ( int i=2; i <= N; ++i ){
		while ( size > 1 && area2( idx[size - 2], Y[ idx[size - 2] ], idx[size - 1], Y[idx[size - 1]], i, Y[i] ) >= 0 )
			size--;
		idx[ size++ ] = i;
	}
	for ( int i=0; i < size; ++i )
		printf("(%d, %d)\n", idx[i], Y[ idx[i] ]);
	double res = 0;
	int j;
	for ( int i=0; i < size; ++i ){
		while ( j < size && idx[j] - idx[i] < K )
			j++;
		if ( j >= size ) break;
		res = max( res, 1.0*(Y[ idx[j] ] - Y[ idx[i] ])/(idx[j] - idx[i]) );
	}
	printf("%.6f\n", res);
	return 0;
}
