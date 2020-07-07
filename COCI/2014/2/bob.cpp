#include<cstdio>
#include<stack>
using namespace std;
const int MAXN = 1 << 10;
int A[MAXN][MAXN];
int H[MAXN][MAXN];
long long ans[MAXN][MAXN];

stack<int> V;	// Value
stack<int> P;	// Position

int main(){
	int N, M;
	
	scanf("%d %d", &N, &M);
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < M; ++j )
			scanf("%d", A[i] + j);
	// Find the "Height"
	for ( int j=0; j < M; ++j ) H[0][j] = 1;
	for ( int i=1; i < N; ++i )
		for ( int j=0; j < M; ++j )
			H[i][j] = ( A[i][j] == A[i - 1][j] )? (H[i - 1][j] + 1):1;
	
	long long res = 0;
	int last, plast;
	for ( int i=0; i < N; ++i ){
		last = -1;
		plast = -1;
		for ( int j=0; j < M; ++j ){
			if ( A[i][j] != last ){ // clean the stacks
				while ( !V.empty() )
					V.pop(), P.pop();
				V.push( H[i][j] ), P.push( j );
				last = A[i][j], plast = j;
				ans[i][j] = H[i][j];
			}
			else {
				while ( !V.empty() && V.top() >= H[i][j] )
					V.pop(), P.pop();
				if ( V.empty() ){
					ans[i][j] = (j - plast + 1) * H[i][j];
				}
				else {
					ans[i][j] = (j - P.top()) * H[i][j];
					ans[i][j] += ans[ i ][ P.top() ];
				}
				V.push( H[i][j] ), P.push( j );
			}
			res += ans[i][j];
		}
	}
	printf("%lld\n", res);
	return 0;
}
