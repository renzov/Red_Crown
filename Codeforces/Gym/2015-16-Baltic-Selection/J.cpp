#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN = 612;
typedef pair<int,int> pii;

int N, M;
char G[MAXN][MAXN];
int d[MAXN][MAXN];
int dx[] = {0, -1, 0, 1};
int dy[] = {-1, 0, 1, 0};

int main(){
	int A, B;
	scanf("%d %d %d %d", &M, &N, &A, &B);

	for ( int i = 0; i < N; ++i ){
		scanf("%s", G[i]);
		fill( d[i], d[i] + M, -1 );
	}
	
	int x, y, nx, ny;
	queue<pii> Q;

	d[0][0] = 0;
	Q.push( pii(0, 0) );
	while ( !Q.empty() ){
		x = Q.front().first;
		y = Q.front().second;
		Q.pop();
		
		for ( int i = 0; i < 4; ++i ){
			nx = x + dx[i];
			ny = y + dy[i];
			if ( nx < 0 || ny < 0 || nx >= N || ny >= M || d[nx][ny] != -1 || G[nx][ny] == '#' )
				continue;
			d[nx][ny] = d[x][y] + 1;
			Q.push( pii(nx, ny) );
		}
	}
	
	if ( d[N - 1][M - 1] == -1 ) puts("IMPOSSIBLE");
	else printf("%d\n", (d[N - 1][M - 1] >> 1) * (A + B) + B * ( d[N - 1][M - 1] & 1 ) );

	return 0;
}
