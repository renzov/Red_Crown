#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN = 5005;

int X[MAXN];
int Y[MAXN];
int X2[MAXN];
int Y2[MAXN];

int N;
int A, B;
vector<int> P[MAXN];

int in[MAXN];

void process(){
	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d %d", X + i, Y + i);
		X2[i] = X[i], Y2[i] = Y[i];
	}
	// Compress coordinates
	sort( X2, X2 + N );
	sort( Y2, Y2 + N );
	A = unique( X2, X2 + N ) - X2;
	B = unique( Y2, Y2 + N ) - Y2;
	for ( int i=0; i < N; ++i ){
		X[i] = lower_bound( X2, X2 + A, X[i] ) - X2;
		Y[i] = lower_bound( Y2, Y2 + B, Y[i] ) - Y2;
	}
	// Represent the points as linked lists
	int x, y;
	for ( int i=0; i < N; ++i ){
		x = X[i], y = Y[i];
		P[x].push_back(y);
	}
	
	int cnt;
	long long res = 0;
	for ( int i=1; i < A; ++i ){
		// Set the y coordinates
		for ( int k=0; k < (int)P[i].size(); ++k ){
			y = P[i][k];
			in[ y ] = 1;
		}
		for ( int j=0; j < i; ++j ){
			cnt = 0;
			for ( int k=0; k < (int)P[j].size(); ++k ){
				y = P[j][k];
				cnt += in[ y ];
			}
			res += ( 1LL * ( cnt - 1 ) * cnt ) >> 1;
		}
		// Undo the marking
		for ( int k=0; k < (int)P[i].size(); ++k ){
			y = P[i][k];
			in[ y ] = 0;
		}
	}
	printf("%lld\n", res);
}


int main(){
	int runs;
	scanf("%d", &runs);
	for ( int i=1; i <= runs; ++i ){
		printf("Case %d: ", i);
		process();
		for ( int i=0; i < A; ++i )	
			P[i].clear();
	}
	return 0;
}

