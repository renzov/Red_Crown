#include<cstdio>
using namespace std;
const int MAXN = 128;
int N, M;

char B[MAXN][MAXN];
int deg[MAXN][MAXN] = {0};
bool vis[MAXN][MAXN] = {0};

int dx[] = {0, -1, 0, 1, 1, -1, 1, -1};
int dy[] = {1, 0, -1, 0, 1, -1, -1, 1};

inline bool in( const int &x, const int &y ){
	return x >= 0 && x < N && y >= 0 && y < M;
}

bool dfs( const int &x, const int &y ){
	vis[x][y] = true;
	
	bool res = deg[x][y] == 2;
	int nx, ny;

	for ( int k=0; k < 8; ++k ){
		nx = x + dx[k], ny = y + dy[k];
		if ( in( nx, ny ) && B[nx][ny] == '#' && !vis[nx][ny] )
			res &= dfs( nx, ny );
	}
	return res;
}

int main(){

	scanf("%d %d", &N, &M);
	for ( int i=0; i < N; ++i )
		scanf("%s", B[i]);

	int x, y;
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < M; ++j )
			for ( int k=0; k < 8; ++k ){
				x = i + dx[k];
				y = j + dy[k];
				if ( in(x, y) && B[x][y] == '#' )
					deg[i][j]++;
			}
	
	int res = 0;

	for ( int i=0; i < N; ++i )
		for ( int j=0; j < M; ++j )
			if ( B[i][j] == '#' && !vis[i][j] && dfs( i, j ) ){
				res++;
			}
	
	printf("%d\n", res);
	return 0;
}
