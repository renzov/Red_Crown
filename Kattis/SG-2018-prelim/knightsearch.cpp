#include<cstdio>
using namespace std;
const int MAXN = 128;
int N;
bool possible[MAXN][MAXN][10];
bool vis[MAXN][MAXN][10];
char T[MAXN][MAXN];
char S[] = "ICPCASIASG";
int dx[] = {2, -2, 2, -2, 1, -1, 1, -1};
int dy[] = {1, 1, -1, -1, 2, 2, -2, -2};

bool dfs( const int &x, const int &y, const int &p ){
	if ( p == 9 ) return true;
	if ( vis[x][y][p] ) return possible[x][y][p];
	vis[x][y][p] = true;
	int nx, ny;
	bool found = false;
	for ( int k=0; k < 8 && !found; ++k ){
		nx = x + dx[k], ny = y + dy[k];
		if ( nx < 0 || nx >= N || ny < 0 || ny >= N ) continue;
		if ( T[nx][ny] == S[p+1] ){
			if ( !vis[nx][ny][p+1] )
				found |= dfs( nx, ny, p + 1 );
			else 
				found |= possible[nx][ny][p + 1];
		}
	}
	return possible[x][y][p] = found;
}

int main(){	
	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		for ( int j=0; j < N; ++j ){
			scanf(" %c", T[i] + j);
			for ( int k=0; k < 10; ++k )
				vis[i][j][k] = false;
		}
	}
	
	bool found = false;
	for ( int i=0; i < N && !found; ++i )
		for ( int j=0; j < N && !found; ++j )
			if ( T[i][j] == 'I' )
				found |= dfs( i , j , 0 );
	puts( found? "YES":"NO" );
	return 0;
}
