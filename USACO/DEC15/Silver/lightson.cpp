#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef pair<int,int> pii;
const int MAXN = 128;

int dx[] = {0, -1, 0, 1};
int dy[] = {1, 0, -1, 0};

int N, M;
int ans = 0;

bool visited[MAXN][MAXN];
bool lit[MAXN][MAXN];
vector<pii> S[MAXN][MAXN];

inline bool in( const int &x, const int &y ){
	return x >= 0 && x < N && y >= 0 && y < N;
}

bool can_visit( const int &x, const int &y ){
	int nx, ny;
	for ( int i = 0; i < 4; ++i ){
		nx = x + dx[i];
		ny = y + dy[i];
		if ( in( nx, ny ) && visited[nx][ny] )
			return true;
	}
	return false;
}

void dfs( const int &x, const int &y ){
	visited[x][y] = true;
	int nx, ny;
	// first activate the switches and visit
	for ( int i = 0; i < (int)S[x][y].size(); ++i ){
		nx = S[x][y][i].first;
		ny = S[x][y][i].second;
		if ( !lit[nx][ny] ){
			lit[nx][ny] = true;
			ans++;
			if ( can_visit( nx, ny ) )
				dfs( nx, ny );
		}
	}
	// visit adjacent vertices that are lit
	for ( int i = 0; i < 4; ++i ){
		nx = x + dx[i];
		ny = y + dy[i];
		if ( in( nx, ny ) && !visited[nx][ny] && lit[nx][ny] )
			dfs( nx, ny );
	}  
}

int main(){
	freopen("lightson.in", "r", stdin );
	freopen("lightson.out", "w", stdout );

	scanf("%d %d", &N, &M);
		
	int x1, y1, x2, y2;
	for ( int i = 0; i < M; ++i ){
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		x1--, x2--, y1--, y2--;
		S[x1][y1].push_back( pii(x2, y2) );
	}
	
	ans = 1;
	lit[0][0] = true;
	dfs( 0, 0 );
	printf("%d\n", ans );
	return 0;
}
