#include<cstdio>
#include<algorithm>
#include<vector>
#include<cassert>
using namespace std;
typedef pair<int,int> pii;

const int MAXN = 8;
const int FREE = -2;

int R[MAXN][MAXN];
int C[MAXN][MAXN];
int board[MAXN][MAXN];
int N, M;
int ans;
int B;
int rows, cols;
vector<bool> usedR;
vector<bool> usedC;
int free_rows, free_cols;
vector<pii> barrier;
vector<int> cnt;
vector< vector<int> > G;
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
vector<pii> pos;

bool max_matching(){
	return true;
}

bool backtrack( const int &idx, const int &res ){

}

bool gen_solution(){
	int x, y, nx, ny, deg;
	for ( int i = 0; i < (int)barrier.size(); ++i ){
		x = barrier[i].first, y = barrier[i].second;
		deg = 0;
		for ( int j = 0; j < 4; ++j ){
			nx = x + dx[j];
			ny = y + dy[j];
			if ( nx < 0 || ny < 0 || nx >= N || ny >= M || board[nx][ny] != FREE ) continue;
			pos.push_back( pii(nx, ny) );
			deg++;
		}
		if ( cnt[i] >= 0 && deg < cnt[i] ) return false;
	}
	usedR = vector<bool>( rows, false );
	usedC = vector<bool>( cols, false );
	return backtrack(0, 0);
}

void number_cells( int matrix[MAXN][MAXN], const int &n, const int &m, int &idx ){
	int last = -1;
	idx = 0;
	for ( int i = 0; i < n; ++i ){
		for ( int j = 0; j < m; ++j ){
			if ( board[i][j] == FREE ){
				matrix[i][j] = idx;
			}
			else {
				matrix[i][j] = -1;
				if ( last != -1 ) idx++;
			}
			last = matrix[i][j];
		}
		idx++;
		last = -1;
	}
}

void create_bipartite_graph(){
	G = vector< vector<int> >( rows, vector<int>() );
	int u, v;
	for ( int i = 0; i < N; ++i )
		for ( int j = 0; j < M; ++j )
			if ( R[i][j] != -1 ){
				u = R[i][j];
				v = C[j][i];
				assert( u != -1 && v != -1 );
				G[u].push_back(v);
			}
}

void process(){
	int x, y, z;
	
	scanf("%d", &B);
	for ( int i = 0; i < B; ++i ){
		scanf("%d %d", &x, &y, &z);
		x--, y--;
		board[x][y] = z;
		barrier.push_back( pii(x, y) );
		cnt.push_back( z );
	}
	number_cells( R, N, M, rows );
	number_cells( C, M, N, cols );
	create_bipartite_graph();
	if ( rows == cols && gen_solution() )
		printf("%d\n", ans);
	else 
		puts("No solution");
}

void init(){
	barrier.clear();
	cnt.clear();
	for ( int i = 0; i < N; ++i )
		for ( int j = 0; j < M; ++j )
			board[i][j] = FREE;
}

int main(){
	while ( scanf("%d %d", &N, &M) && (N || M) ){
		init();
		process();
	}
	return 0;
}
