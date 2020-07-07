#include<cstdio>
#include<algorithm>
using namespace std;
typedef pair<int,int> point;
#define X first
#define Y second
const int MAXN = 505;

point P[2*MAXN];
int cnt[MAXN][MAXN];
int cntB[MAXN];

inline bool below( const point &A, const point &B, const point &C ){
	return (1LL*(B.X - A.X)*(C.Y - A.Y) - 1LL*(C.X - A.X)*(B.Y - A.Y)) < 0;
}

int main(){
	int N, M;
	int numP;

	scanf("%d %d", &N, &M);
	// Read the points
	for ( int i=0; i < N; ++i )
		scanf("%d %d", &P[i].X, &P[i].Y);
	sort( P, P + N );

	for ( int i=N; i < N + M; ++i )
		scanf("%d %d", &P[i].X, &P[i].Y);
	
	for ( int i=0; i < N - 1; ++i )
		for ( int j=i+1; j < N; ++j )
			for ( int k=N; k < N + M; ++k )
				if ( P[k].X >= P[i].X && P[k].X <= P[j].X && below(P[i], P[j], P[k]) )
					cnt[i][j]++;

	for ( int i=0; i < N; ++i )
		for ( int j=N; j < N + M; ++j )
			if ( P[i].X == P[j].X && P[j].Y < P[i].Y )
				cntB[i]++;

	int res = 0;
	// count the triangles
	for ( int i=0; i < N - 2; ++i )
		for ( int j=i + 1; j < N - 1; ++j )
			for ( int k=j + 1; k < N; ++k ){
				numP = cnt[i][j] + cnt[j][k] - cnt[i][k] - cntB[j];
				if ( !numP ) res++;
			}
	printf("%d\n", res);
	return 0;
}
