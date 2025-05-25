#include<cstdio>
#include<climits>
#include<algorithm>
#include<queue>
using namespace std;
typedef pair<int, int> point;
const int MAXN = 1024;

int dx[] = {0, 1, -1, 0};
int dy[] = {1, 0, 0, -1};
int inv[] = {3, 2, 1, 0};
char dir[] = {'R', 'D', 'U', 'L'};

int N, M;
char grid[MAXN][MAXN];
int d[MAXN][MAXN];
int times[MAXN][MAXN];	// times[x][y] = times position (x, y) was relaxed
int pre[MAXN][MAXN];

bool valid( const int &x, const int &y ){
	return x >= 0 && y >= 0 && x < N && y < M && grid[x][y] != '#';
}

void print_path( const int &x, const int &y ){
	if ( grid[x][y] == 'A' ) return;
	int k = pre[x][y];
	print_path( x + dx[ k ], y + dy[ k ] );
	putchar( dir[ inv[k] ] );
}

void bfs( const char &type, const int &mask ){
	queue<point> q;
	// initialize queue
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < M; ++j )
			if ( grid[i][j] == type ){
				q.push( point(i, j) );
				d[i][j] = 0;
				times[i][j] |= mask;
			}
	
	int x, y, w, nx, ny;
	while ( !q.empty() ){
		x = q.front().first;
		y = q.front().second;
		q.pop();
		
		w = d[x][y] + 1;
		for ( int k=0; k < 4; ++k ){
			nx = x + dx[k];
			ny = y + dy[k];
			if ( valid( nx, ny ) && w < d[nx][ny] ){
				d[nx][ny] = w;
				times[nx][ny] |= mask;
				pre[nx][ny] = inv[k];
				q.push( point(nx, ny) );
			}
		}
	}
}

int main(){
	scanf("%d %d", &N, &M);
	for ( int i=0; i < N; ++i )
		scanf("%s", grid[i]);
	
	for ( int i=0; i < N; ++i )
		fill( d[i], d[i] + M, INT_MAX );
	
	bfs('M', 1);
	bfs('A', 2);
	// look if there is a position
	int ex = -1, ey = -1;
	for ( int i=0; i < N; ++i ){
		if ( grid[i][0] != '#' && times[i][0] > 1 )
			ex = i, ey = 0;
		if ( grid[i][M-1] != '#' && times[i][M-1] > 1 )
			ex = i, ey = M - 1;
	}
	for ( int j=0; j < M; ++j ){
		if ( grid[0][j] != '#' && times[0][j] > 1 )
			ex = 0, ey = j;
		if ( grid[N-1][j] != '#' && times[N-1][j] > 1 )
			ex = N - 1, ey = j;
	}
	// print the answer
	if ( ex == -1 ){
		puts("NO");
	}
	else {
		puts("YES");
		printf("%d\n", d[ex][ey]);
		print_path( ex, ey );
		puts("");
	}
	return 0;
}
