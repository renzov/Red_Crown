#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int MAXN = 1 << 10;

int N, M;
int comp[MAXN][MAXN];
char G[MAXN][MAXN];
vector<int> res;

int dx[] = {0, -1, 0, 1};
int dy[] = {-1, 0, 1, 0};

void dfs( const int &x, const int &y, const int &c ){
	comp[x][y] = c;
	
	int nx, ny;
	for ( int i=0; i < 4; ++i ){
		nx = x + dx[i];
		ny = y + dy[i];
		if ( nx < 0 || ny < 0 || nx >= N || ny >= M )
			continue;
		if ( G[nx][ny] == '*' ) res[c]++;
		else if ( comp[nx][ny] == -1 ) dfs(nx, ny, c);
	}
}

int main(){
	int K;	

	scanf("%d %d %d", &N, &M, &K);
	
	for ( int i = 0; i < N; ++i ){
		scanf("%s", G[i]);
		fill( comp[i], comp[i] + M, -1);
	}

	for ( int i = 0; i < N; ++i )
		for ( int j=0; j < M; ++j ){
			if ( G[i][j] == '.' && comp[i][j] == -1 ){
				res.push_back(0);
				dfs( i, j, (int)res.size() - 1 );
			}
		}
	
	int x, y;
	while ( K-- ){
		scanf("%d %d", &x, &y);
		x--, y--;
		printf("%d\n", res[ comp[x][y] ] );
	}
	return 0;
}
