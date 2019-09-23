#include<cstdio>
#include<climits>
#include<queue>
#include<algorithm>
#include<vector>
using namespace std;
typedef pair<int,int> pii;
const int MAXN = 64;

char T[MAXN][MAXN];
int cmp[MAXN][MAXN];
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
vector<pii> C[4];
int d[4][MAXN][MAXN];
int D[4][4];
int N, M;

void dfs( const int &x, const int &y, const int &col ){
	cmp[x][y] = col;
	C[col].push_back( pii(x, y) );
	int nx, ny;
	for ( int k=0; k < 4; ++k ){
		nx = x + dx[k];
		ny = y + dy[k];
		if ( nx < 0 || nx >= N || ny < 0 || ny >= M ) continue;
		if ( T[nx][ny] == 'X' && !cmp[nx][ny] )
			dfs( nx, ny, col );
	}
}

void bfs( const int &col ){
	queue<pii> q;
	int x, y;
	int nx, ny;
	
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < M; ++j )
			d[col][i][j] = -1;

	for ( int i=0; i < (int) C[col].size(); ++i ){
		x = C[col][i].first, y = C[col][i].second;
		q.push( C[col][i] );
		d[col][x][y] = 0;
	}
	while ( !q.empty() ){
		x = q.front().first, y = q.front().second;
		q.pop();
		for ( int k=0; k < 4; ++k ){
			nx = x + dx[k];
			ny = y + dy[k];
			if ( nx < 0 || nx >= N || ny < 0 || ny >= M ) continue;
			if ( d[col][nx][ny] == -1 ){
				d[col][nx][ny] = d[col][x][y] + 1;
				q.push( pii(nx, ny) );
			}
		}
	}
}

int main(){
	
	scanf("%d %d", &N, &M);
	for ( int i=0; i<N; ++i )
		scanf("%s", T[i]);

	// Mark the components
	int cnt = 0;
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < M; ++j )
			if ( T[i][j] == 'X' && !cmp[i][j] )
				dfs( i, j, ++cnt );
			
	// find shortest path
	for ( int k=1; k <= 3; ++k )
		bfs( k );

	// find distance between components
	int val, x, y;
	for ( int k=1; k < 3; ++k ){
		for ( int i=k+1; i <= 3; ++i ){
			val = INT_MAX;
			for ( int j=0; j < (int)C[i].size(); ++j ){
				x = C[i][j].first, y = C[i][j].second;
				val = min( val, d[k][x][y] );
			}
			D[i][k] = D[k][i] = val - 1;	// Number of cell between those points 
		}
	}

	int res = INT_MAX;
	// Test anchor point
	for ( int i=0; i<N; ++i  )
		for ( int j=0; j<M; ++j )
			if ( !cmp[i][j] )
				res = min( res, d[1][i][j] + d[2][i][j] + d[3][i][j] - 2 );

	// Test each component as anchor
	res = min( res, D[1][2] + D[1][3] );
	res = min( res, D[2][1] + D[2][3] );
	res = min( res, D[3][1] + D[3][2] );
	
	printf("%d\n", res);
	return 0;
}
