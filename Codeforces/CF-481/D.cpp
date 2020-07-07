#include<cstdio>
#include<algorithm>
#include<climits>
using namespace std;
const int MAXN = 100005;
int A[MAXN];
int N;
int w;

int find_sol( const int &i, const int &last ){
	if ( i >= N ) return 0;
	for ( int j=-1; j <= 1; ++j ){
		if ( (A[ i ] + j) - last == w ){
			int v = find_sol( i + 1, A[i] + j );
			if ( v < INT_MAX ) return v + abs(j);
			else return INT_MAX;
		} 
	}
	return INT_MAX;
}

int main(){
	scanf("%d", &N);
	for ( int i=0; i < N; ++i )
		scanf("%d", A + i);
	
	if  ( N <= 2 ){
		printf("0\n");
	}
	else {
		int res = INT_MAX;
		int val;
		for ( int i=-1; i <= 1; ++i )
			for ( int j=-1; j <= 1; ++j ){
				w = (A[1] + j) - (A[0] + i);
				val = find_sol( 2, A[1] + j );
				if ( val < INT_MAX )
					res = min( res, val + abs(i) + abs(j) );
			}
		if ( res < INT_MAX ) printf("%d\n", res);
		else puts("-1");
	}
	return 0;
}
