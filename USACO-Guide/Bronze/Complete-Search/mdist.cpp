#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 5005;
int X[MAXN];
int Y[MAXN];

inline int dist( const int &i, const int &j ){
	return (X[i] - X[j])*(X[i] - X[j]) + (Y[i] - Y[j])*(Y[i] - Y[j]);
}

int main(){
	int N;

	scanf("%d", &N);
	for ( int i=0; i < N; ++i )
		scanf("%d", X + i);
	
	for ( int i=0; i < N; ++i )
		scanf("%d", Y + i);

	int res = 0;
	for ( int i=0; i < N; ++i )
		for ( int j=i + 1; j < N; ++j )
			res = max( res, dist( i , j ) );
	printf("%d\n", res);
	return 0;
}
