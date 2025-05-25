#include<cstdio>
using namespace std;
const int MAXN = 1024;

int N, M;

int dx[4] = {0, 1, -1, 0};
int dy[4] = {-1, 0, 0, 1};

char grid[MAXN][MAXN];
int dfsn[MAXN][MAXN];
int num = 0;

bool valid( const int &x, const int &y ){
	// a position is valid if it remains inside the grid and the position contains a floor
	return x >= 0 && y >= 0 && x < N && y < M && grid[x][y] == '.';
}

void dfs( const int &x, const int &y ){
	int nx, ny;

	dfsn[x][y] = ++num;
	for ( int k=0; k < 4; ++k ){
		nx = x + dx[k];
		ny = y + dy[k];
		if ( valid( nx, ny ) && dfsn[nx][ny] == 0 )
			dfs( nx, ny );
	}
}

int main(){

	scanf("%d %d", &N, &M);
	for ( int i=0; i < N; ++i )
		scanf("%s", grid[i] );

	int ans = 0;

	for ( int i=0; i < N; ++i )
		for ( int j=0; j < M; ++j ) 
			if ( grid[i][j] == '.' && dfsn[i][j] == 0 ){
				dfs( i, j );
				ans++;
			}

	printf("%d\n", ans);
	return 0;
}
