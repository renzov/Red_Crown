#include<cstdio>
#include<climits>
#include<algorithm>
#include<queue>
using namespace std;
const int MAXN = 1024;
typedef pair<int, int> point;

int N, M;

int dx[4] = {0, 1, -1, 0};
int dy[4] = {-1, 0, 0, 1};
int inv[4] = {3, 2, 1, 0};			// inverse for each direction
char dir[4] = {'L','D','U','R'};	// letter representing each direction

char grid[MAXN][MAXN];
int pre[MAXN][MAXN];
int d[MAXN][MAXN];

void print_ans( const int &x, const int &y ){	
	if ( grid[x][y] == 'A' ) return;	// reach the beginning
	
	int k = pre[x][y]; // direction to go to previous cell
	int px = x + dx[k];
	int py = y + dy[k];

	print_ans( px, py );
	putchar( dir[ inv[k] ] );
}

bool valid( const int &x, const int &y ){
	// a position is valid if it remains inside the grid and the position is not a wall
	return x >= 0 && y >= 0 && x < N && y < M && grid[x][y] != '#';
}
	
void bfs( const int &sx, const int &sy, const int &ex, const int &ey ){
	// Initialize distances
	for ( int i=0; i < N; ++i )
		fill( d[i], d[i] + M, INT_MAX );

	queue<point> q;	
	
	d[sx][sy] = 0;
	q.push( point(sx, sy) );

	int x, y;
	int nx, ny;

	while ( !q.empty() ){
		x = q.front().first;
		y = q.front().second;
		q.pop();

		if ( x == ex && y == ey ) break;

		for ( int k=0; k < 4; ++k ){
			nx = x + dx[k];
			ny = y + dy[k];
			if ( valid( nx, ny ) && d[nx][ny] == INT_MAX ){
				pre[nx][ny] = inv[k];
				d[nx][ny] = d[x][y] + 1;
				q.push( point( nx, ny ) );
			}
		}
	}

	if ( d[ex][ey] < INT_MAX ){
		puts("YES");
		printf("%d\n", d[ex][ey]);
		print_ans( ex, ey );
		puts("");
	}
	else {
		puts("NO");
	}

}

int main(){

	scanf("%d %d", &N, &M);
	for ( int i=0; i < N; ++i )
		scanf("%s", grid[i] );

	int sx, sy, ex, ey;
	
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < M; ++j ) 
			if ( grid[i][j] == 'A' )
				sx = i, sy = j;
			else if ( grid[i][j] == 'B' )
				ex = i, ey = j;

	bfs( sx, sy, ex, ey );
	return 0;
}

